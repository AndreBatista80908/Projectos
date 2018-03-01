package pex.app.main;

import pex.app.evaluator.EvaluatorMenu;
import pt.utl.ist.po.ui.Command;
import pt.utl.ist.po.ui.InputString;
import pt.utl.ist.po.ui.Menu;
import pt.utl.ist.po.ui.Display;
import pt.utl.ist.po.ui.Form;
import pex.app.App;
import pex.core.Program;
import pex.app.evaluator.EvaluatorMenu;

/**
 * Open menu for managing programs.
 */
public class EditProgram extends Command<App> {

    /**
     * @param receiver
     */
    public EditProgram(App receiver) {
        super(Label.MANAGE_PROGRAM, receiver);
    }

    /** @see pt.utl.ist.po.ui.Command#execute() */
    @Override
    public final void execute() {
        Form f = new Form(title());
        InputString s = new InputString(f, Message.requestProgramId());
        f.parse();

        Program _prog = entity().getInterpreter().getProgram(s.value());
        if (_prog != null){
            EvaluatorMenu eMenu = new EvaluatorMenu(_prog);
            eMenu.open();
        } else {
            Display display = new Display(title());
            display.addNewLine(Message.noSuchProgram(s.value()));
            display.display();
        }
    }
}
