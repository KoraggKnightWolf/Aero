class CommandDeop : public Command
{
 public:
        CommandDeop(Module* Creator) : Command(Creator,"DEOP", 1)
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
                        modes.push_back("-o");
                        modes.push_back(user->nick);

                        ServerInstance->SendGlobalMode(modes, ServerInstance->FakeClient);
                        return CMD_SUCCESS;
                }

                return CMD_FAILURE;
        }
};

class ModuleDeOp : public Module
{
        CommandDeop cmd;
 public:
        ModuleDeOp() : cmd(this)
        {
        }

        void init()
        {
                ServerInstance->Modules->AddService(cmd);
        }

        virtual ~ModuleDeOp()
        {
        }

        virtual Version GetVersion()
        {
                return Version("Provides oped users with the ability to deop themselves.", VF_VENDOR);
        }
};

MODULE_INIT(ModuleDeOp)
