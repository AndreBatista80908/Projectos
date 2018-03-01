package pex.app.main;

import java.io.IOException;
import pt.utl.ist.po.ui.Command;
import pt.utl.ist.po.ui.Display;
import pt.utl.ist.po.ui.Form;
import pt.utl.ist.po.ui.InputString;
import pt.utl.ist.po.ui.InvalidOperation;
import pex.app.App;
import pex.core.Interpreter;

/**
 * Write (save) program to file.
 */
public class WriteProgram extends Command<App> {

    /**
     * @param receiver
     */
    public WriteProgram(App receiver) {
        super(Label.WRITE_PROGRAM, receiver);
    }

    /** @see pt.utl.ist.po.ui.Command#execute() */
    @Override
    public final void execute() throws InvalidOperation{
        Form f = new Form(title());
        InputString programId = new InputString(f, Message.requestProgramId());
        InputString file = new InputString(f, Message.programFileName());
        f.parse();
        Interpreter _interp = entity().getInterpreter();
        if(_interp.containProgram(programId.value())){
            _interp.writeProgram(programId.value(), file.value());
        }
        else{
            Display display = new Display(title());
            display.addNewLine(Message.noSuchProgram(programId.value()));
            display.display();
        }
    }
}
