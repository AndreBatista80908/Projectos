package pex.app.evaluator;

import java.util.*;
import pex.core.Program;
import java.util.Set;
import pex.app.App;
import pex.core.Program;
import pex.core.Interpreter;
import pex.core.expression.Identifier;
import pt.utl.ist.po.ui.Display;

/**
 * Show all program identifiers.
 */
public class ShowAllIdentifiers extends ProgramCommand {

    /**
     * @param receiver
     */
    public ShowAllIdentifiers(Program receiver) {
        super(Label.SHOW_ALL_IDENTIFIERS, receiver);
    }

    @Override
    public final void execute() {

    }
}
