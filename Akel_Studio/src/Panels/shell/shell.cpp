// This file is a part of Akel Studio
// Authors : @kbz_8
// Created : 10/07/2021
// Updated : 06/02/2023

#include <Panels/shell/shell.h>

Shell::Shell(std::shared_ptr<Ak::ELTM> eltm) : Parser()
{
	_eltm = eltm;
}

std::string Shell::exec(std::string command)
{
#ifdef AK_PLATFORM_LINUX
	std::array<char, 128> buffer;
    std::string result;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(command.c_str(), "r"), pclose);

    if(!pipe)
	{
        print("unkown command", 1);
		return "";
	}

    while(fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr)
        result += buffer.data();

    return result;
#else
	print("unkown command", 1);
	return "";
#endif
}

void Shell::command(std::string command)
{
	ee = false;
	print("> " + command);
	Command com = Parser::parse(std::move(command));

	switch(com)
	{
		case Command::clear:
			if(!Parser::getOptions().empty())
			{
				print(_eltm->getText("errors.consoleNoOpt"), 1);
				break;
			}
			if(!Parser::getArg().empty())
			{
				print(_eltm->getText("errors.consoleTooMuchArgs"), 1);
				break;
			}
			_history = _out;
			_out.clear();
		break;

		case Command::history:
			if(!Parser::getOptions().empty())
			{
				print(_eltm->getText("errors.consoleNoOpt"), 1);
				break;
			}
			if(!Parser::getArg().empty())
			{
				print(_eltm->getText("errors.consoleTooMuchArgs"), 1);
				break;
			}
			_out.insert(_out.end(), _history.begin(), _history.end());
		break;

		case Command::build:
			if(!Parser::getOptions().empty())
			{
				print(_eltm->getText("errors.consoleNoOpt"), 1);
				break;
			}
			if(!Parser::getArg().empty())
			{
				print(_eltm->getText("errors.consoleTooMuchArgs"), 1);
				break;
			}
		break;

		case Command::quit:
			if(!Parser::getOptions().empty())
			{
				print(_eltm->getText("errors.consoleNoOpt"), 1);
				break;
			}
			if(!Parser::getArg().empty())
			{
				print(_eltm->getText("errors.consoleTooMuchArgs"), 1);
				break;
			}
			_quit = true;
		break;

		case Command::easterEgg:
			if(!Parser::getOptions().empty())
			{
				print(_eltm->getText("errors.consoleNoOpt"), 1);
				break;
			}
			if(!Parser::getArg().empty())
			{
				print(_eltm->getText("errors.consoleTooMuchArgs"), 1);
				break;
			}
			print("RICK ROLL TIME !!!" , 2);
			ee = true;
		break;

		case Command::sysShell:
		{
			std::string sys_command;
			for(auto it = Parser::getArg().begin(); it != Parser::getArg().end(); it++)
			{
				if(std::holds_alternative<Command>(*it))
					sys_command += Parser::_keywords[std::get<Command>(*it)];
				else
					sys_command += std::get<std::string>(*it);
			}
			print(std::move(exec(sys_command)), 2);
			break;
		}

		case Command::error:
		default: print(_eltm->getText("errors.consoleUnknownCommand"), 1); break;
	}
}

