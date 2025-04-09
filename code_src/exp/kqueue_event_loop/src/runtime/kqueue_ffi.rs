#![allow(non_camel_case_types, non_snake_case)]
// src/runtime/kqueue_ffi.rs

use libc::{c_int, c_void, intptr_t, timespec, uintptr_t};

// Define the kevent struct based on libc definition for macOS/BSD
#[derive(Debug, Clone, Copy)] // Removed Default
#[repr(C)]
pub struct kevent {
    pub ident: uintptr_t,  // identifier for this event
    pub filter: i16,       // filter for event
    pub flags: u16,        // action flags for kq
    pub fflags: u32,       // filter flag value
    pub data: intptr_t,    // filter data value
    pub udata: *mut c_void, // opaque user data identifier
}

// Constants for kqueue filters and flags (common values)
// Filters
pub const EVFILT_READ: i16 = -1;
// pub const EVFILT_WRITE: i16 = -2; // Not used in this example

// Flags
pub const EV_ADD: u16 = 0x1; // add event to kq (implies enable)
pub const EV_ENABLE: u16 = 0x4; // enable event
#[allow(unused)]
pub const EV_DELETE: u16 = 0x2; // delete event from kq
pub const EV_CLEAR: u16 = 0x20; // clear event state after retrieval (ET simulation)
// pub const EV_ONESHOT: u16 = 0x10; // only report one occurrence

extern "C" {
    pub fn kqueue() -> c_int;

    // timespec can be null for indefinite wait
    pub fn kevent(
        kq: c_int,
        changelist: *const kevent,
        nchanges: c_int,
        eventlist: *mut kevent,
        nevents: c_int,
        timeout: *const timespec,
    ) -> c_int;

    // We still need close
    pub fn close(fd: c_int) -> c_int;
}

// Wrapper for our event structure
#[derive(Debug)]
pub struct Event(pub kevent); // Tuple struct wrapping kevent

impl Event {
    // Helper to get the token (udata) back as usize
    pub fn token(&self) -> usize {
        self.0.udata as usize
    }
}
