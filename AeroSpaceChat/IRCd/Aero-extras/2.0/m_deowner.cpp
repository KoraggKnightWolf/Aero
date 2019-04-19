class CommandDeowner : public Command
{
 public:
        CommandDeowner(Module* Creator) : Command(Creator,"DEOWNER", 1)
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
                        modes.push_back("-q");
                        modes.push_back(user->nick);

                        ServerInstance->SendGlobalMode(modes, ServerInstance->FakeClient);
                        return CMD_SUCCESS;
                }

                return CMD_FAILURE;
        }
};

class ModuleDeOwner : public Module
{
        CommandDeowner cmd;
 public:
        ModuleDeOwner() : cmd(this)
        {
        }

        void init()
        {
                ServerInstance->Modules->AddService(cmd);
        }

        virtual ~ModuleDeOwner()
        {
        }

        virtual Version GetVersion()
        {
                return Version("Provides owner'ed users with the ability to deowner themselves.", VF_VENDOR);
        }
};

MODULE_INIT(ModuleDeOwner)
