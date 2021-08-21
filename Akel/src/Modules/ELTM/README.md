<p align="center">
    <img src="https://github.com/Kbz-8/Akel/blob/main/Ressources/eltm_logo.png" alt="drawing" width="500"/>
</p>

# ELTM
ELTM (Extension Language for Text Management) is a C++ extension language for C++ that allows you to manage your project texts more easily
with Akel.
Its use is not dissociable from C++ because it needs an instanciated context
context to use it. It is extremely simple and requires little time to
to learn it.

===========================================================

	// comment
	/*
	   Long
	   Comment
	*/

	import someFile.tm

	set YourID = your text
	set ID2 = (this is
		   a very
		   very long
		   text)
	set something = get(ID2)	// get() is used to get text from another ID

	begin module moduleName

		set yay = bla bla bla
		set ouh = get(something)

	end module

============================================================

In your C++ project :

	Ak::ELTMcontext context;
	if(context.newContext("file.tm") == true)	// Ak::ELTMcontext::newContext return true or false in case of good execution or error in your ELTM file
	{
		std::string text = context.getText("YourID"); // return "your text" in std::string
		std::cout << context.getText("moduleName.yay") << std::endl;
		std::cout << Ak::ELTMcontext::getText("YourID") << std::endl; // you can get texts directly from ELTMcontext class if context was initialized
	}

## Documentations
[ELTM 1.0](https://github.com/Kbz-8/Akel/blob/dev/Akel/src/Modules/ELTM/ELTM_documentation_1_0.pdf)
[ELTM 1.1](https://github.com/Kbz-8/Akel/blob/dev/Akel/src/Modules/ELTM/ELTM_documentation_1_1.pdf)
