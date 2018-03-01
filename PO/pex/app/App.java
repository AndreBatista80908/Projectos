package pex.app;

import pex.AppIO;
import pex.core.Program;
import pex.core.Interpreter;
import pex.app.main.MainMenu;
import pex.parser.NewParser;
import pex.parser.ParserException;
import pt.utl.ist.po.ui.Display;
import pt.utl.ist.po.ui.Form;
import pt.utl.ist.po.ui.InputString;
import pt.utl.ist.po.ui.InputInteger;

import java.io.Serializable;

/**
 * This is a sample client for the expression evaluator.
 * It uses a text-based user interface.
 */
public class App implements AppIO , Serializable {

    private Interpreter _interp;

    public App(){
        _interp = new Interpreter(this);
    }

    public Interpreter getInterpreter(){
        return _interp;
    }

    public void newInterpreter(){
        _interp = new Interpreter(this);
    }

    public void setInterpreter(Interpreter interpreter) {
        _interp = interpreter;
    }

    /**
     * Writes a string to be presented to the user.
     *
     * @param str the string to write
     **/
    public void println(String str) {
        Display display = new Display();
        display.addNewLine(str).display();
    }

    /**
     * Reads a string inputed by the user.
     *
     * @return the string written by the user.
     **/
    public String readString() {    
        Form f = new Form("");
        InputString s = new InputString(f, "");
        f.parse();
        return s.value();
    }

    /**
     * Reads an integer inputed by the user.
     *
     * @return the number written by the user.
     **/
    public int readInteger() {
        Form f = new Form("");
        InputInteger i = new InputInteger(f, "");
        f.parse();
        return i.value();
    }

    /**
     * @param args
     */
    public static void main(String[] args) {
        
        App app = new App();
        String datafile = System.getProperty("import"); //$NON-NLS-1$
        NewParser psr = new NewParser();
        if (datafile != null) {
            try {
		        Program _prog = psr.parseFile(datafile, "import", app.getInterpreter());
                app.getInterpreter().addProgram(_prog);
            } catch (ParserException e) {
                e.printStackTrace();
            }
        }
        MainMenu menu = new MainMenu(app);
        menu.open();
    }
}
