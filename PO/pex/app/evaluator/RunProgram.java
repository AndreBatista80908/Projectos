package pex.app.evaluator;

import pex.core.Program;
import pt.utl.ist.po.ui.Display;
import pex.app.BadExpressionException;

/**
 * Run program.
 */
public class RunProgram extends ProgramCommand {
  
    /**
     * @param receiver
     */
    public RunProgram(Program receiver) {
        super(Label.RUN_PROGRAM, receiver);
    }

    @Override
    public final void execute(){
        Display display = new Display();
        try{
        entity().execute();
        } catch (BadExpressionException e){
            display.addNewLine(e.getMessage()).display();
        }
    }
}
