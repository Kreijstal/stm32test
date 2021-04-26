// This is a comment, and is ignored by the compiler
// You can test this code by clicking the "Run" button over there ->
// or if you prefer to use your keyboard, you can use the "Ctrl + Enter" shortcut

#![no_std]
// This code is editable, feel free to hack it!
// You can always return to the original code by clicking the "Reset" button ->
#[no_mangle]
#[export_name="test"]
pub extern "C" fn test()->i32{
     2+2
}
// This is the main function
//fn main() {
    // Statements here are executed when the compiled binary is called

    // Print text to the console
  //  println!("Hello World!");
//}
//
#[panic_handler]
fn my_panic(_info: &core::panic::PanicInfo) -> ! {
        loop {}
}
