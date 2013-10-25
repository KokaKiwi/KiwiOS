#[link(
    name = "KiwiOS",
    vers = "0.2.0",
    desc = "A small kernel written in Rust",
    author = "KokaKiwi <kokakiwi@kokakiwi.net>"
)];

#[no_std];
#[feature(globs)];

#[path = "rust-core/core/mod.rs"]
mod core;
mod io;

#[no_mangle]
pub fn start()
{
    loop {}
}

#[no_mangle]
pub unsafe fn __morestack()
{
}
