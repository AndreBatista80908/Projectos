package pex.app.main;

import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.FileNotFoundException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import pt.utl.ist.po.ui.Command;
import pt.utl.ist.po.ui.Form;
import pt.utl.ist.po.ui.Display;
import pt.utl.ist.po.ui.InputString;
import pt.utl.ist.po.ui.InvalidOperation;
import pex.app.App;
import pex.core.Interpreter;

/**
 * Open existing interpreter.
 */
public class Open extends Command<App> {

    /**
     * @param receiver
     */
    public Open(App receiver) {
        super(Label.OPEN, receiver);
    }

    /** @see pt.tecnico.po.ui.Command#execute() */
    @Override
    public final void execute() throws InvalidOperation {
    	Form f = new Form(title());
    	InputString file = new InputString(f,Message.openFile());
    	f.parse();
        try{
            ObjectInputStream in = new ObjectInputStream(new FileInputStream(file.value()));
            Interpreter _interp = (Interpreter)in.readObject();
            in.close();
            entity().setInterpreter(_interp);
        }
        catch(FileNotFoundException e){
            Display display = new Display();
            display.addNewLine(Message.fileNotFound()).display();
        } catch(ClassNotFoundException e) {
            e.printStackTrace();
        } catch(IOException e) {
            e.printStackTrace();
        }
    }
}
