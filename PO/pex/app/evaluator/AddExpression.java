package pex.app.evaluator;

import pex.app.BadExpressionException;
import pex.app.BadPositionException;
import pex.core.Program;
import pt.utl.ist.po.ui.Form;
import pt.utl.ist.po.ui.InputString;

/**
 * Add expression.
 */
public class AddExpression extends ProgramCommand {

    /**
     * @param receiver
     */
    public AddExpression(Program receiver) {
        super(Label.ADD_EXPRESSION, receiver);
    }
    
    @Override
    public final void execute() throws BadExpressionException, BadPositionException {
        Form f = new Form(title());
        InputString idx = new InputString(f, Message.requestPosition());
        InputString expression = new InputString(f, Message.requestExpression());
        f.parse();
        entity().addExpression(expression.value(), idx.value());
    }
}
