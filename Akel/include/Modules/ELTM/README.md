<p align="center">
    <img src="https://github.com/SpinWaves/Akel/blob/main/Resources/assets/eltm_logo.png" alt="drawing" width="500"/>
</p>

# ELTM
ELTM (Extension Language for Text Management) is a C++ extension language that allows you to manage the texts of your projects more easily with Akel.
Its use is not dissociable from C++ because it requires an instantiated context to use it. It is extremely simple and requires little time to learn.

===========================================================

Your ELTM code :

```
// comment
/*
	Long
	Comment
*/

import "someFile.eltm"

let YourID = "your text"
let ID2 = "that s
		a very
		very long
		text"
let something = get(ID2)	// get() is used to get text from another ID

begin module myModule
	let yay = "bla bla bla"
	let ouh = "this is the text from 'something' : "get(something)
end module
```

============================================================

In your C++ project :
```cpp
Ak::ELTM context;
if(context.load("file.eltm"))	// Ak::ELTM::load return true or false in case of good execution or error in your ELTM file
{
	std::string text = context.getText("YourID");
	std::cout << context.getText("myModule.yay") << std::endl;
}
```
