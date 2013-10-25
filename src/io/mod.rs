
pub fn outb<T>(port: u16, val: T)
{
    unsafe
    {
        asm!("outb %al, %dx" :: "{dx}" (port), "{al}" (val) :: "volatile");
    }
}

pub fn inb<T>(port: u16) -> T
{
    unsafe
    {
        let mut val: T;
        asm!("inb %dx, %al" : "={al}" (val) : "{dx}" (port) :: "volatile");
        val
    }
}
