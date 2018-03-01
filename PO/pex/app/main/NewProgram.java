package pex.app.main;

import pt.utl.ist.po.ui.Command;
import pt.utl.ist.po.ui.Form;
import pt.utl.ist.po.ui.InputString;
import pex.app.App;
import pex.core.Program;

/**
 * Create new program.
 */
public class NewProgram extends Command<App> {

    /**
     * @param receiver
     */
    public NewProgram(App receiver) {
        super(Label.NEW_PROGRAM, receiver);
    }

    /** @see pt.utl.ist.po.ui.Command#execute() */
    @Override
    public final void execute() {
        Form f = new Form(title());
        InputString s = new InputString(f, Message.requestProgramId());
        f.parse();
        Program _prog = new Program(s.value(), entity().getInterpreter());
        entity().getInterpreter().addProgram(_prog);
    }
}
