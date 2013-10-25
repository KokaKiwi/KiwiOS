#[link(
    name = "KiwiOS",
    vers = "0.2.0",
    desc = "A small kernel written in Rust",
    author = "KokaKiwi <kokakiwi@kokakiwi.net>"
)];

#[no_std];
#[feature(globs)];

use core::option::*;

#[path = "rust-core/core/mod.rs"]
mod core;

#[no_mangle]
pub unsafe fn start()
{
    loop {}
}

#[no_mangle]
pub unsafe fn __morestack()
{
}
