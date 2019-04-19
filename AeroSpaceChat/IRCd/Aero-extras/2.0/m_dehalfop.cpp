#include "inspircd.h"

/** Handle /DEVOICE
 */
class CommandDehalfop : public Command
{
 public:
        CommandDehalfop(Module* Creator) : Command(Creator,"DEHALFOP", 1)
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
                        modes.push_back("-h");
                        modes.push_back(user->nick);

                        ServerInstance->SendGlobalMode(modes, ServerInstance->FakeClient);
                        return CMD_SUCCESS;
                }

                return CMD_FAILURE;
        }
};

class ModuleDeHalfOp : public Module
{
        CommandDehalfop cmd;
 public:
        ModuleDeHalfOp() : cmd(this)
        {
        }

        void init()
        {
                ServerInstance->Modules->AddService(cmd);
        }

        virtual ~ModuleDeHalfOp()
        {
        }

        virtual Version GetVersion()
        {
                return Version("Provides halfoped users with the ability to dehalfop themselves.", VF_VENDOR);
        }
};

MODULE_INIT(ModuleDeHalfOp)
