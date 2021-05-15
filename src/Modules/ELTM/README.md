# ELTM
ELTM (Extension Language for Text Management) is a micro language used by your c++ code to manage the texts of your projects. It's pretty simple.
There is a short example of it's use :

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

	AE::ELTMcontext context;
	if(context.newContext("file.tm") == true)	// AE::ELTMcontext::newContext return true or false in case of good execution or error in your ELTM file
	{
		std::string text = context.getText("YourID"); // return "your text" in std::string
		std::cout << context.getText("moduleName.yay") << std::endl;
	}

