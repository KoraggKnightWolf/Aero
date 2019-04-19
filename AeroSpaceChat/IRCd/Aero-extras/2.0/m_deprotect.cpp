class CommandDeprotect : public Command
{
 public:
        CommandDeprotect(Module* Creator) : Command(Creator,"DEPROTECT", 1)
        {
                syntax = "<channel>";
                TRANSLATE2(TR_TEXT, TR_END);
        }

        CmdResult Handle (const std::vector<std::string> &parameters, User *user)
        {
                Channel* c = ServerInstance->FindChan(parameters[0]);
                if (c && c->HasUser(user))
                {
                        std::vector<std::string> modes;
                        modes.push_back(parameters[0]);
                        modes.push_back("-a");
                        modes.push_back(user->nick);

                        ServerInstance->SendGlobalMode(modes, ServerInstance->FakeClient);
                        return CMD_SUCCESS;
                }

                return CMD_FAILURE;
        }
};

class ModuleDeProtect : public Module
{
        CommandDeprotect cmd;
 public:
        ModuleDeProtect() : cmd(this)
        {
        }

        void init()
        {
                ServerInstance->Modules->AddService(cmd);
        }

        virtual ~ModuleDeProtect()
        {
        }

        virtual Version GetVersion()
        {
                return Version("Provides protected users with the ability to deprotect themselves.", VF_VENDOR);
        }
};

MODULE_INIT(ModuleDeProtect)
