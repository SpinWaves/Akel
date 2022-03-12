<p align="center">
    <img src="https://github.com/SpinWaves/Akel/blob/main/Ressources/assets/eltm_logo.png" alt="drawing" width="500"/>
</p>

# ELTM
ELTM (Extension Language for Text Management) is a C++ extension language that allows you to manage the texts of your projects more easily with Akel.
Its use is not dissociable from C++ because it requires an instantiated context to use it. It is extremely simple and requires little time to learn.

===========================================================

Your ELTM code :

```kotlin
// comment
/*
	Long
	Comment
*/

import someFile.tm

set YourID = your text
set ID2 = (that s
		a very
		very long
		text)
set something = get(ID2)	// get() is used to get text from another ID

begin module moduleName

	set yay = bla bla bla
	set ouh = get(something)

end module
```

============================================================

In your C++ project :
```C++
Ak::ELTM context;
if(context.load("file.eltm"))	// Ak::ELTM::load return true or false in case of good execution or error in your ELTM file
{
	std::string text = context.getText("YourID"); // return "your text" in std::string
	std::cout << context.getText("moduleName.yay") << std::endl;
	std::cout << Ak::ELTM::getText("YourID") << std::endl; // you can get texts directly from ELTM class if context was initialized
}
```
[Documentation](https://github.com/SpinWaves/Akel/blob/main/Akel/src/Modules/ELTM/ELTM_documentation_1_1.pdf)
