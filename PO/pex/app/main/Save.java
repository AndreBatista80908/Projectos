package pex.app.main;

import java.io.IOException;
import pt.utl.ist.po.ui.Command;
import pt.utl.ist.po.ui.Form;
import pt.utl.ist.po.ui.InputString;
import pt.utl.ist.po.ui.InvalidOperation;
import pex.app.App;
import pex.core.Interpreter;

/**
 * Save to file under current name (if unnamed, query for name).
 */
public class Save extends Command<App> {

    /**
     * @param receiver
     */
    public Save(App receiver) {
        super(Label.SAVE, receiver);
    }

    /** @see pt.utl.ist.po.ui.Command#execute() */
    @Override
    public final void execute() throws InvalidOperation {
        if(entity().getInterpreter().getName() == null){
            Form f = new Form(title());
            InputString s = new InputString(f, Message.newSaveAs());
            f.parse();
            entity().getInterpreter().setName(s.value());
            entity().getInterpreter().save(s.value());
        } else
            entity().getInterpreter().save(entity().getInterpreter().getName());
    }
}
