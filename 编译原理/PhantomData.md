> Who has a good understanding of PhantomData, its purpose, and what the table in the nomicon (variance, contravariance, invariance, etc) means?

# What is `PhantomData<T>`

The two defining properties of `PhantomData<T>` are the following:

- At runtime, `PhantomData<T>` is exactly like `()`, *i.e.*, nothing.
  - This gives the peace of mind of it being (a) zero-cost (abstraction)
- For compile-time analysis, `PhantomData<T>` is exactly like `T`
  - The usefulness of such a thing may not be obvious at first glance, but it turns out that types have properties (or more precisely, they can *lack* properties), which in turn leads to the containing struct transitively lacking these properties too.

## (Some) Type Properties

### 1) `auto trait`s

The most intuitive of these "properties" are `auto trait`s (*a.k.a.*, OIBITs, as [@cuviper](https://users.rust-lang.org/u/cuviper) said). These are (marker) traits that any type implements, unless the type contains / is made of some specific type that does not implement it. So instead of "allow-listing" the implementors of the trait, as usual, one goes and "deny-lists" the root non-implementors of the trait.

#### Example

Imagine wanting to have a (marker) trait for types of data that is truly immutable when behind a shared reference:

```rust
trait ImmutableIfAliased {}
```

In Rust, data behind a shared reference is immutable unless it contains somewhere an `UnsafeCell<_>`, the root element behind all the constructions offering aliased mutability / interior mutabilty (`Cell`, `RefCell`, `Mutex`, `RwLock`). So this makes for a nice candidate of a deny-list approach:

```rust
/// If a type does not contain any `!ImmutableIfAliased` stuff,
/// and if it is not  excplicitely marked `!ImmutableIfAliased`
/// itself, then it automagically becomes `ImmutableIfAliased`
auto
trait ImmutableIfAliased {}

struct Foo {
    x: i32,
}

const_assert_clauses!( Foo : ImmutableIfAliased );
```

And now let's "deny-list" `UnsafeCell`:

```rust
impl<T : ?Sized> !ImmutableIfAliased for UnsafeCell<T> {}
```

- `UnsafeCell<T> : ImmutableIfAliased` scratched successfully 

Now, if the trait was made `unsafe` (to implement), then this could be used in a generic function `<T : ImmutableIfAliased>` to know that the data pointed to by a `&T` is truly immutable (at least for the duration of the reference).

### 2) `'static` lifetime *vs*. genericity

It turns out that being `'static` is also one such property: a struct is `'static` as longs as it does not contain a non-`'static` element:

```rust
const_assert_clauses!( Foo : 'static );
```

As soon as a struct contains an element with a lifetime parameter that is not `'static` (*i.e.*, a generic lifetime parameter), then the whole struct becomes generic and tied to this lifetime parameter:

```rust
struct FancyReferenceToAnInteger<'lifetime> (
    &'lifetime i32,
);
```

In other words, a type genericity "infects" the containing type, which, in turn, becomes generic too:

```rust
enum Option<T> {
    None,
    Some(T),
}
```

------

## Applications to `PhantomData<_>`

### 1) `impl !Trait`

In stable Rust (at least as of `1.37`), one cannot "unimplement" / deny-list an `auto trait`:

```rust
struct CannotBeSharedAcrossThreads {
    // fields
}
impl !Sync for CannotBeSharedAcrossThreads {}
```

yields

```rust
error[E0658]: negative trait bounds are not yet fully implemented; use marker types for now
```

This can be circumvented thanks to the infectious nature of the `!Sync` property: since for all types `T`, `Cell<T>` is not `Sync`, we could go and add an unused `Cell<T>` field to `CannotBeSharedAcrossThreads`:

```rust
struct CannotBeSharedAcrossThreads {
    // fields
    _unused: Cell<i32>,
}
```

Now our type is soundly not `Sync`, but it does have to carry an extra data field, integer-sized. It can be made smaller, as `Cell<u8>`, or even actually zero-sized / non-existent at runtime, with `Cell<()>`:

```rust
struct CannotBeSharedAcrossThreads {
    // fields
    _unused: Cell<()>, // weird: are we intending to mutate `()` ?
}
```

but this only works because we could choose any `T` for our `Cell<T>` (plus it would be sound for `Cell<()>` to be `Sync`, since ZSTs cannot be mutated, and in that case our abstraction would break). In some cases, we may need to use a type that has no zero-sized-version of its properties.

That's when `PhantomData` shines: `PhantomData<T>` has all the properties (and lack thereof) that `T` has, while also being guaranteed to be zero-sized:

```rust
type PhantomNotSync = PhantomData<Cell<u8>>;

struct CannotBeSharedAcrossThreads {
    // fields
    _not_sync: PhantomNotSync, // => impl !Sync for CannotBeSharedAcrossThreads 
}
```

we can also have a `PhantomNotSendNorSync`:

```rust
type PhantomNotSendNorSync = PhantomData<&'static Cell<u8>>;
```

with which we can create `PhantomNotSend`:

```rust
#[derive(Default)]
pub
struct PhantomNotSend (
    PhantomNotSendNorSync,
);
// Protect the type from being infected by `!Sync`
unsafe impl Sync for PhantomNotSend {}
```

### 2) Adding type/lifetime parameters: artificially generic structs

In a similar fashion to unimplementing `auto trait`s, one may want to have a struct have a(n additional) type or lifetime parameter, despite it not really having a generic type. One such case is when trying to define pointer types less restrictive / with weaker semantics than Rust references, but not as raw as plain pointers.

#### Example: out references

Let's imagine we want to have an API working with so-called "out pointers" for the sake of performance (or to enable more complex stack pinning abstractions):

```rust
// instead of
fn get_ft ()
  -> i32
{
    42
}

// do 
fn write_ft (out: &'_ mut i32)
  -> &'_ mut i32
{
    *out = 42;
    out
}
```

Now, `write_ft` works fine, but it requires that the caller have already initialized the memory where `write_ft` writes (having a `&mut i32` point to uninitialised memory is currently UB).

It would be nice to have an API like the following:

```rust
struct OutRef<'a, T : 'a> { ... }

impl<'a, T : 'a> OutRef<'a, T> {
    fn write (self: OutRef<'a, T>, value: T)
      -> &'a mut T
    { ... }
}

impl<T> MaybeUninit<T> {
    fn as_out_ref(self: &'_ mut MaybeUninit<T>)
      -> Out<'_, T>
    { ... }
}

impl<'a, T : 'a> From<&'a mut T> for OutRef<'a, T> { ... }
```

This way we could write:

```rust
fn write_ft (out: OutRef<'_, i32>)
  -> &'_ mut i32
{
    out.write(42)
}

fn main ()
{
    let mut x = MaybeUninit::<i32>::uninit();
    let at_x = x.as_out_ref();
    // drop(x);
    let x: &mut i32 = write_ft(at_x);
}
```

The fact that `OutRef` includes a lifetime parameter, that is then used in the `as_out_ref` method to force the borrow on the `MaybeUninit` to live as long the the `OutRef` lives, makes it so that if the `drop(x)` line is uncommented, the program no longer compiles.
Whereas if we had used `MaybeUninit`'s `.as_mut_ptr()` as our "out pointer", then the program (with the uncommented drop) would have compiled despite it being unsound.

#### Implementation

`OutRef` is nothing more than a raw pointer:

```rust
struct OutRef<'a, T : 'a> {
    ptr: *mut T,
}
```

which leads to a compilation error due to the parameter `'a` not being used (if this were accepted, then the struct would be bivariant over `'a`, thus allowing to cast any `OutRef<'a, T>` to `OutRef<'static, T>`, and we would be back to just having a raw pointer (*i.e.*, **it is not the outer genericity that matters, but how the generic parameters are used within a struct**)):

```rust
struct OutRef<'a, T : 'a> {
    ptr: *mut T,
    _lifetime: PhantomData<&'a ()>,
}
```

So, much like in the `!Sync` case and `Cell`, we have used here the type `&'a ()` since it *is* generic over `'a`, and then wrapped it in a `PhantomData` to make it be a zero-cost abstraction.

Then we implement the rest of our imagined API:

```rust
// Invariant: ptr points to a valid `MaybeUninit<T>`
pub
struct OutRef<'a, T : 'a> {
    ptr: *mut T,
    _lifetime: PhantomData<&'a ()>,
}

impl<'a, T : 'a> OutRef<'a, T> {
    pub
    fn write (self: OutRef<'a, T>, value: T)
      -> &'a mut T
    {
        unsafe {
            // # Safety
            //
            //   - this is `MaybeUninit<T>::write`
            self.ptr.write(value);
            &mut *self.ptr
        }
    }
}

pub
trait MaybeUninitExt<T> {
    fn as_out_ref (self: &'_ mut Self)
      -> OutRef<'_, T>
    ;
}
impl<T> MaybeUninitExt<T> for MaybeUninit<T> {
    fn as_out_ref(self: &'_ mut MaybeUninit<T>)
      -> OutRef<'_, T>
    {
        #[allow(unused_unsafe)]
        unsafe {
            // # Safety
            //
            //   - Respects the invariant
            OutRef {
                ptr: self.as_mut_ptr(),
                _lifetime: PhantomData,
            }
        }
    }
}

impl<'a, T : 'a> From<&'a mut T> for OutRef<'a, T> {
    #[inline]
    fn from (p: &'a mut T)
      -> OutRef<'a, T>
    {
        #[allow(unused_unsafe)]
        unsafe {
            // # Safety
            //
            //   - Respects the invariant, since something
            //     init can be seen as maybeuninit
            OutRef {
                ptr: p,
                _lifetime: PhantomData,
            }
        }
    }
}
```

- [Playground](https://play.rust-lang.org/?version=stable&mode=debug&edition=2018&gist=e2827cc8759d6f06d21852a3fb685f22)

#### Non-Zero optimisation

So, everything is actually quite fine, but our struct is not as optimal as it could be. More precisely,

```rust
Option<OutRef<'_, T>>
```

is not pointer-sized, which is a pity, since given our invariant, we know that our pointer is not null. Luckily, the `::core` library offers a handy structure for non-nullable raw pointers: [`ptr::NonNull`](https://play.rust-lang.org/?version=stable&mode=debug&edition=2018&gist=786871d107e8e5b6797f46b581179962), with which we hurry and update our struct definition:

```rust
struct OutRef<'a, T : 'a> {
    ptr: ptr::NonNull<T>,
    _lifetime: PhantomData<&'a ()>,
}
```

- [Playground](https://play.rust-lang.org/?version=stable&mode=debug&edition=2018&gist=db48a89a08ede4464d22b71e043b5b5b)

Hooray, all is good, in our brave new code!

Except when someome comes and posts that our library is **unsound**, since [it allows the following code to compile](https://play.rust-lang.org/?version=stable&mode=debug&edition=2018&gist=898b8e3c8f16f7df07ff8ddc7b013383):

```rust
fn main ()
{
    let mut s: &'static str = "Static str"; // s pointer to static str
    let at_s = OutRef::<&'static str>::from(&mut s); // pointer to s
    {
        let s = String::from("Short-lived str");
        at_s.write(&s); // override s with a pointer to the short-lived str
    }
    dbg!(s); // Use after free!
}
```

Now, you may be wondering, why did such obviously wrong code compile? Was the compiler not paying attention?

Well, let me tell you: unless your code is *cooler* than ICE, the compiler does not miss anything. Rust accompanies us at each step of our path, very gently pulling our hand when we are too close to falling onto a (safety) hole, and also very gently letting us fall all the way down the hole, as soon we spell the forbidden incantation: `unsafe`.

And we have indeed used `unsafe`, more precisely, we have written:

```rust
struct OutRef<'a, T : 'a> {
    ptr: ptr::NonNull<T>,
    _lifetime: PhantomData<&'a ()>,
}

impl<'a, T : 'a> OutRef<'a, T> {
    pub
    fn write (self: OutRef<'a, T>, value: T)
      -> &'a mut T
    {
        unsafe {
            // # Safety
            //
            //   - this is `MaybeUninit<T>::write`
            self.ptr.write(value);
            &mut *self.ptr
        }
    }
```

Now, the problem with this code can be incredibly tricky to spot, since it involves one of the most arcane mechanics of the language:

## Variance (informally)

Variance is the property involved when trying to **sub-type**. Sub-typing is a process whereby `T1` is said to be a subtype of a type `T2` (I will write it as `T1 : T2`) if the compiler accepts any expression of type `T1` where the type `T2` was expected.

> Oh, like when Rust accepts any reference to an array `&[T; N]` where a reference to a slice `&[T]` is expected? Or when Rust accepts a `Box<T : Trait>` where a `Box<dyn Trait>` is expected? Or when a `&String` becomes a `&str`?

Nope, nope, and nope. All these cases are (implicit) *coercions*, meaning that a *transformation* takes place:

- `&[T; N] == *const T` becomes `&[T] == (*const T, usize)`,
- `Box<T>` becomes `Box<dyn Trait> = (Box<TypeErased>, *const Trait::VTable)`
- `&String` becomes `&str` by `Deref`erence of `String`: it's actually `&*String`

Subtyping, on the other hand, does not involve tranformation, just compiler type-level tolerance.

#### A macro to check variance

One good way to check for subtyping is with the following macro (AFAIK, no (implicit) coercions behind a raw pointer):

```rust
macro_rules! const_assert_subtypes {(
    for [<$($generics:tt)*]
    $T1:ty : $($T2:tt)*
) => (
    const _: () = {
        fn foo<$($generics)* (x: *const $T1)
          -> *const $($T2)*
        {
             x
        }
    };
)}

const_assert_subtypes!(
    for [<T>]
    T : T
);

const_assert_subtypes!(
    for [<'a, T>]
    &'static T : &'a T
);

const_assert_subtypes!(
    for [<'a, 'b, T>]
    &'b T : &'a T
    where 'b : 'a
);

const_assert_subtypes!(
    for [<'a, 'b : 'a, T>]
    fn(&'a T) : fn(&'b T)
);

const_assert_subtypes!(
    for [<'a, 'b : 'a, T>]
    &'b mut T : &'a mut T
);

// Errors
// const_assert_subtypes!(
//     for [<'a, 'b : 'a>]
//     &'a mut &'b () : &'a mut &'a ()
// );
```

- [Playground](https://play.rust-lang.org/?version=stable&mode=debug&edition=2018&gist=94054414a293c5a18ef4e02385c7e11f)

So now that we know some examples of subtyping, let's try to summarize them:

- Rust only subtypes regarding lifetimes: if `'a : 'b` (read "if the lifetime `'a` lives at least as long as `'b`"), then `&'a T` is a subtype of `&'b T`: hence the famous "lifetimes can shrink".
- Subtyping builds up by using compound types.

> Variance is then the property of a **generic** type (that is, asking for the variance of a non-generic type makes no sense) *w.r.t.* how different monomorphisations of the type may subtype each other.

Example: given the `type Ref<'a> = &'a ()`, we know that `Ref<'a> : Ref<'b>` when / where `'a : 'b`. In that case, `Ref` is said to be covariant.

- > `F<T>` is said to be covariant iff for all `T1 : T2 => F<T1> : F<T2>`

  - in other words: `F` *preserves* subtyping

  Examples:

  - `type F<T> = T;`

  - Thus, we also have:
    **`type F<T> = PhantomData<T>;`**

  - When `T<'a> = &'a [mut] _`, this gives:

    `type F<'a> = &'a ();`
    `type F<'a> = &'a u8;`
    `type F<'a> = &'a Whatever;`

    `type F<'a> = &'a mut ();`
    `type F<'a> = &'a mut u8;`
    `type F<'a> = &'a mut Whatever;`

  - `type F<T> = Box<T>;`
    `type F<T> = [A]Rc<T>;`
    `type F<T> = *const T;`
    `type F<T> = ptr::NonNull<T>;`

  - More generally, covariance is the usual behavior, and the exceptions are the examples in the other categories of variance.

- > `F<T>` is said to be contravariant iff for all `T1 : T2 => F<T2> : F<T1>`

  - in other words: `F` *reverses* subtyping

  Example:

  - `type F<T> = fn(T, ...) -> Whatever`

- > `F<T>` is said to be bivariant iff it is both covariant and contravariant.

  - This could be theoretically be possible for the function `fn id<T> (x: T) -> T { x }`, but in practice there is no bivariance in Rust

- > `F<T>` is said to be invariant iff it is neither covariant nor contravariant.

  Examples:

  - The main rule is the following: mutation usually leads to invariance;
    More specifically: **non owning-mutation has to be invariant**:
  - `type F<T> = &'whatever mut T` being the best known case,
    - With `T<'a> = &'a Whatever`, it gives:
      `type F<'a> = &'whatever mut &'a Whatever`
    - Careful:
      `type F<'a, T> = &'a mut T` is invariant in `T` but is **covariant in `'a`**
  - `type F<T> = *mut T;`
  - `UnsafeCell<T>` is also invariant (it is *the* mutability wrapper by definition).

This, by the way, shows *the only difference* between `*const _` and `*mut _`: the former is covariant, whereas the latter is not (=> invariant).

### Back to the soundness issue

Let's recap the code with the soundness issue:

```rust
struct OutRef<'a, T : 'a> {
    ptr: ptr::NonNull<T>,
    _lifetime: PhantomData<&'a ()>,
}

impl<'a, T : 'a> OutRef<'a, T> {
    pub
    fn write (self: OutRef<'a, T>, value: T)
      -> &'a mut T
    {
        unsafe {
            // # Safety
            //
            //   - this is `MaybeUninit<T>::write`
            self.ptr.write(value);
            &mut *self.ptr
        }
    }
}

fn main ()
{
    let mut s: &'static str = "Static str"; // s pointer to static str
    let at_s = OutRef::<&'static str>::from(&mut s); // pointer to s
    {
        let s = String::from("Short-lived str");
        at_s.write(&s); // override s with a pointer to the short-lived str
    }
    dbg!(s); // Use after free!
}
```

So, the problem is that our `OutRef<'a, T>`, which is morally a `&'a mut T` (another implementation, by the way, would have been `&'a mut MaybeUninit<T>`), and should thus be:

- covariant in `'a` ![:white_check_mark:](https://emoji.discourse-cdn.com/twitter/white_check_mark.png?v=12)
  - `&'a ()` is covariant in `'a`
- invariant in `T` ![:x:](https://emoji.discourse-cdn.com/twitter/x.png?v=12)
  - `ptr::NonNull<T>` is covariant in `T` !

So our `OutRef<'_, T>` was covariant in `T`, which means that `OutRef<'_, &'static str>` was a subtype of `OutRef<'_, &'short_lived str>` since `'static : 'short_lived`,
so the call

```rust
at_s.write(&s);
// i.e.
<OutRef<T?>>::write(
    // self: OutRef<T?>
    at_s, // : OutRef<&'static str> : OutRef<&'short_lived str>
    // value: T?
    &s, // : &'short_lived str
); // Thus T? = &'short_lived str
```

was not prevented by Rust, thus allowing to write a pointer to a short lived local where a pointer to a longer lived local was expected; which is unsound, and is the reason why non-owning mutable "references" (of any sort) need to be invariant.

### Solution

If you imagine `Covariant<{"T"}>` as a marker trait for covariance over the generic parameter `T`, then, to get `Invariant<{"T"}> = !Covariant<{"T"}>`, it suffices to have one of the fields of our struct not be covariant in `T`. In our case, the most simple fix is to change our `_lifetime: PhantomData<&'a ()>` field into

```rust
struct OutRef<'a, T : 'a> {
    ptr: ptr::NonNull<T>, // : Covariant<{"T"}>
    _marker: PhantomData<&'a mut T>, // : !Covariant<{"T"}>
}
// => OutRef<T> : !Covariant<{"T"}>
```

which should have been the case anyways, given how our `OutRef` was a form of mutable reference (before the `NonNull<T>` "upgrade", our code was actually sound thanks to having used `*mut T`, invariant, as the pointer type. Had we used `*const T` instead we would have had the same problem).

### Quick rule of thumb about variance in `unsafe` code

When in doubt, **be invariant**! This (potentially conservative) choice is never unsound; it may just hurt some call-site ergonomics for the user of the library / API.

# *Addendum* The "ownership" type property

`PhantomData<T>` may also be used to express ownership over `T` when the struct otherwise uses `T` within a raw pointer, so as to make Rust's drop checker prevent some configurations that could be unsound.

I detailed this usage in [this other post](https://users.rust-lang.org/t/phantomdata-and-dropck-confusion/26624/2).