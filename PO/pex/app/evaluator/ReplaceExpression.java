package pex.app.evaluator;

import pex.app.BadExpressionException;
import pex.app.BadPositionException;
import pex.core.Program;
import pt.utl.ist.po.ui.Form;
import pt.utl.ist.po.ui.InputString;

/**
 * Replace expression in program.
 */
public class ReplaceExpression extends ProgramCommand {

    /**
     * @param receiver
     */
    public ReplaceExpression(Program receiver) {
        super(Label.REPLACE_EXPRESSION, receiver);
    }

    @Override
    public final void execute() throws BadExpressionException, BadPositionException {
        Form f = new Form(title());
        InputString idx = new InputString(f, Message.requestPosition());
        InputString expression = new InputString(f, Message.requestExpression());
        f.parse();
        entity().replaceExpression(expression.value(), idx.value());
    }
}
