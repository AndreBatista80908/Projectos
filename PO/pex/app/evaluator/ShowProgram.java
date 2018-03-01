package pex.app.evaluator;

import pex.core.Program;
import pt.utl.ist.po.ui.Display;


/**
 * Show program (present code).
 */
public class ShowProgram extends ProgramCommand {

    /**
     * @param receiver
     */
    public ShowProgram(Program receiver) {
        super(Label.SHOW_PROGRAM, receiver);
    }

    @Override
    public final void execute() {
        Display display = new Display(title());
        display.addNewLine(entity().listExpressions());
        display.display();
    }
}
