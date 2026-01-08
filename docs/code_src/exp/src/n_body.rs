// The Computer Language Benchmarks Game
// https://salsa.debian.org/benchmarksgame-team/benchmarksgame/
//
// Contributed by Mark C. Lewis.
// Modified slightly by Chad Whipkey.
// Converted from Java to C++ and added SSE support by Branimir Maksimovic.
// Converted from C++ to C by Alexey Medvedchikov.
// Modified by Jeremy Zerfas.
// Converted to Rust by Cliff L. Biffle

#![allow(non_upper_case_globals, non_camel_case_types, non_snake_case)]

use std::arch::x86_64::*;
use std::f64::consts::PI;
use std::mem;

struct body {
    position: [f64; 3],
    velocity: [f64; 3],
    mass: f64,
}

const SOLAR_MASS: f64 = 4.*PI*PI;
const DAYS_PER_YEAR: f64 = 365.24;
const BODIES_COUNT: usize = 5;

static mut solar_Bodies: [body; BODIES_COUNT]=[
    body {    // Sun
        mass: SOLAR_MASS,
        position: [0.; 3],
        velocity: [0.; 3],
    },
    body {    // Jupiter
        position: [
             4.84143144246472090e+00,
            -1.16032004402742839e+00,
            -1.03622044471123109e-01
        ],
        velocity: [
             1.66007664274403694e-03 * DAYS_PER_YEAR,
             7.69901118419740425e-03 * DAYS_PER_YEAR,
            -6.90460016972063023e-05 * DAYS_PER_YEAR
        ],
        mass: 9.54791938424326609e-04 * SOLAR_MASS
    },
    body {    // Saturn
        position: [
             8.34336671824457987e+00,
             4.12479856412430479e+00,
            -4.03523417114321381e-01
        ],
        velocity: [
            -2.76742510726862411e-03 * DAYS_PER_YEAR,
             4.99852801234917238e-03 * DAYS_PER_YEAR,
             2.30417297573763929e-05 * DAYS_PER_YEAR
        ],
        mass: 2.85885980666130812e-04 * SOLAR_MASS
    },
    body {    // Uranus
        position: [
             1.28943695621391310e+01,
            -1.51111514016986312e+01,
            -2.23307578892655734e-01
        ],
        velocity: [
             2.96460137564761618e-03 * DAYS_PER_YEAR,
             2.37847173959480950e-03 * DAYS_PER_YEAR,
            -2.96589568540237556e-05 * DAYS_PER_YEAR
        ],
        mass: 4.36624404335156298e-05 * SOLAR_MASS
    },
    body {    // Neptune
        position: [
             1.53796971148509165e+01,
            -2.59193146099879641e+01,
             1.79258772950371181e-01
        ],
        velocity: [
             2.68067772490389322e-03 * DAYS_PER_YEAR,
             1.62824170038242295e-03 * DAYS_PER_YEAR,
            -9.51592254519715870e-05 * DAYS_PER_YEAR
        ],
        mass: 5.15138902046611451e-05 * SOLAR_MASS
    }
];


// Advance all the bodies in the system by one timestep. Calculate the
// interactions between all the bodies, update each body's velocity based on
// those interactions, and update each body's position by the distance it
// travels in a timestep at it's updated velocity.
unsafe fn advance(bodies: *mut body){

    // Figure out how many total different interactions there are between each
    // body and every other body. Some of the calculations for these
    // interactions will be calculated two at a time by using x86 SSE
    // instructions and because of that it will also be useful to have a
    // ROUNDED_INTERACTIONS_COUNT that is equal to the next highest even number
    // which is equal to or greater than INTERACTIONS_COUNT.
    const INTERACTIONS_COUNT: usize = BODIES_COUNT*(BODIES_COUNT-1)/2;
    const ROUNDED_INTERACTIONS_COUNT: usize = INTERACTIONS_COUNT+INTERACTIONS_COUNT%2;

    // It's useful to have two arrays to keep track of the position_Deltas
    // and magnitudes of force between the bodies for each interaction. For the
    // position_Deltas array, instead of using a one dimensional array of
    // structures that each contain the X, Y, and Z components for a position
    // delta, a two dimensional array is used instead which consists of three
    // arrays that each contain all of the X, Y, and Z components for all of the
    // position_Deltas. This allows for more efficient loading of this data into
    // SSE registers. Both of these arrays are also set to contain
    // ROUNDED_INTERACTIONS_COUNT elements to simplify one of the following
    // loops and to also keep the second and third arrays in position_Deltas
    // aligned properly.
    #[derive(Copy, Clone)]
    #[repr(align(16))]
    struct Align16([f64; ROUNDED_INTERACTIONS_COUNT]);

    static mut position_Deltas: [Align16; 3] = [Align16([0.; ROUNDED_INTERACTIONS_COUNT]); 3];
    static mut magnitudes: Align16 = Align16([0.; ROUNDED_INTERACTIONS_COUNT]);

    // Calculate the position_Deltas between the bodies for each interaction.
    {
        let mut k = 0;
        for i in 0..BODIES_COUNT-1 {
            for j in i+1..BODIES_COUNT {
                for m in 0..3 {
                    position_Deltas[m].0[k]=
                        (*bodies.add(i)).position[m]-(*bodies.add(j)).position[m];
                }
                k += 1;
            }
        }
    }

    // Calculate the magnitudes of force between the bodies for each
    // interaction. This loop processes two interactions at a time which is why
    // ROUNDED_INTERACTIONS_COUNT/2 iterations are done.
    for i in 0..ROUNDED_INTERACTIONS_COUNT/2 {

        // Load position_Deltas of two bodies into position_Delta.
        let mut position_Delta = [mem::MaybeUninit::<__m128d>::uninit(); 3];
        for m in 0..3 {
            position_Delta[m].as_mut_ptr().write(*(&position_Deltas[m].0 as *const f64 as *const __m128d).add(i));
        }
        let position_Delta: [__m128d; 3] = mem::transmute(position_Delta);

        let distance_Squared: __m128d = _mm_add_pd(
            _mm_add_pd(
                _mm_mul_pd(position_Delta[0], position_Delta[0]),
                _mm_mul_pd(position_Delta[1], position_Delta[1]),
            ),
            _mm_mul_pd(position_Delta[2], position_Delta[2]),
        );

        // Doing square roots normally using double precision floating point
        // math can be quite time consuming so SSE's much faster single
        // precision reciprocal square root approximation instruction is used as
        // a starting point instead. The precision isn't quite sufficient to get
        // acceptable results so two iterations of the Newtonâ€“Raphson method are
        // done to improve precision further.
        let mut distance_Reciprocal: __m128d =
          _mm_cvtps_pd(_mm_rsqrt_ps(_mm_cvtpd_ps(distance_Squared)));
        for _ in 0..2 {
            // Normally the last four multiplications in this equation would
            // have to be done sequentially but by placing the last
            // multiplication in parentheses, a compiler can then schedule that
            // multiplication earlier.
            distance_Reciprocal=_mm_sub_pd(
                _mm_mul_pd(distance_Reciprocal, _mm_set1_pd(1.5)),
                _mm_mul_pd(
                    _mm_mul_pd(
                        _mm_mul_pd(_mm_set1_pd(0.5), distance_Squared),
                        distance_Reciprocal,
                    ),
                    _mm_mul_pd(distance_Reciprocal, distance_Reciprocal),
                ));
        }

        // Calculate the magnitudes of force between the bodies. Typically this
        // calculation would probably be done by using a division by the cube of
        // the distance (or similarly a multiplication by the cube of its
        // reciprocal) but for better performance on modern computers it often
        // will make sense to do part of the calculation using a division by the
        // distance_Squared which was already calculated earlier. Additionally
        // this method is probably a little more accurate due to less rounding
        // as well.
        (magnitudes.0.as_mut_ptr() as *mut __m128d).add(i).write(
            _mm_mul_pd(
                _mm_div_pd(_mm_set1_pd(0.01), distance_Squared),
                distance_Reciprocal,
            ));
    }

    // Use the calculated magnitudes of force to update the velocities for all
    // of the bodies.
    {
        let mut k = 0;
        for i in 0..BODIES_COUNT-1 {
            for j in i+1..BODIES_COUNT {
                // Precompute the products of the mass and magnitude since it can be
                // reused a couple times.
                let i_mass_magnitude=(*bodies.add(i)).mass*magnitudes.0[k];
                let j_mass_magnitude=(*bodies.add(j)).mass*magnitudes.0[k];
                for m in 0..3 {
                    (*bodies.add(i)).velocity[m]-=position_Deltas[m].0[k]*j_mass_magnitude;
                    (*bodies.add(j)).velocity[m]+=position_Deltas[m].0[k]*i_mass_magnitude;
                }
                k += 1;
            }
        }
    }

    // Use the updated velocities to update the positions for all of the bodies.
    for i in 0..BODIES_COUNT {
        for m in 0..3 {
            (*bodies.add(i)).position[m]+=0.01*(*bodies.add(i)).velocity[m];
        }
    }
}


// Calculate the momentum of each body and conserve momentum of the system by
// adding to the Sun's velocity the appropriate opposite velocity needed in
// order to offset that body's momentum.
unsafe fn offset_Momentum(bodies: *mut body){
    for i in 0..BODIES_COUNT {
        for m in 0..3 {
            (*bodies.add(0)).velocity[m]-=
                (*bodies.add(i)).velocity[m]*(*bodies.add(i)).mass/SOLAR_MASS;
        }
    }
}


// Output the total energy of the system.
unsafe fn output_Energy(bodies: *mut body){
    let mut energy=0.;
    for i in 0..BODIES_COUNT {

        // Add the kinetic energy for each body.
        energy+=0.5*(*bodies.add(i)).mass*(
            (*bodies.add(i)).velocity[0]*(*bodies.add(i)).velocity[0]+
            (*bodies.add(i)).velocity[1]*(*bodies.add(i)).velocity[1]+
            (*bodies.add(i)).velocity[2]*(*bodies.add(i)).velocity[2]);

        // Add the potential energy between this body and every other body.
        for j in i+1..BODIES_COUNT {
            let mut position_Delta = [mem::MaybeUninit::<f64>::uninit(); 3];
            for m in 0..3 {
                position_Delta[m].as_mut_ptr().write((*bodies.add(i)).position[m]-(*bodies.add(j)).position[m]);
            }
            let position_Delta: [f64; 3] = mem::transmute(position_Delta);

            energy-=(*bodies.add(i)).mass*(*bodies.add(j)).mass/f64::sqrt(
              position_Delta[0]*position_Delta[0]+
              position_Delta[1]*position_Delta[1]+
              position_Delta[2]*position_Delta[2]);
        }
    }

    // Output the total energy of the system.
    println!("{:.9}", energy);
}


pub fn main() {
    unsafe {
        offset_Momentum(solar_Bodies.as_mut_ptr());
        output_Energy(solar_Bodies.as_mut_ptr());
        let c = std::env::args().nth(1).unwrap().parse().unwrap();
        for _ in 0..c { advance(solar_Bodies.as_mut_ptr()) }
        output_Energy(solar_Bodies.as_mut_ptr());
    }
}