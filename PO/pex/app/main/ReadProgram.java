package pex.app.main;

import pt.utl.ist.po.ui.Command;
import pt.utl.ist.po.ui.Form;
import pt.utl.ist.po.ui.InputString;
import pex.app.App;
import pex.core.Program;

/**
 * Read existing program.
 */
public class ReadProgram extends Command<App> {

    /**
     * @param receiver
     */
    public ReadProgram(App receiver) {
        super(Label.READ_PROGRAM, receiver);
    }

    /** @see pt.utl.ist.po.ui.Command#execute() */
    @Override
    public final void execute() {
        Form f = new Form(title());
        InputString s = new InputString(f, Message.programFileName());
        f.parse();
        entity().getInterpreter().readProgram(s.value(),entity().getInterpreter());
    }   
}
