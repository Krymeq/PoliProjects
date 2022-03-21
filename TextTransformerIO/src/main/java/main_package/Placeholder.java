package main_package;

/**
 * Class used to store pre- and post transformation data.
 */
public class Placeholder {
    /**
     * Text to be transformed
     */
    private String text;
    /**
     * ID of the class used for transformation, go to TransformController.answer for more
     */
    private int classID;
    /**
     * ID of the function used for transformation, go to TransformController.answer for more
     */
    private int functionID;

    /**
     * Empty, default constructor, required by Jackson
     */
    public Placeholder(){}

    /**
     * Main constructor initializing each field in the object
     * @param text Text to be transformed
     * @param classID ID of the class used for transformation, go to TransformController.answer for more
     * @param functionID ID of the function used for transformation, go to TransformController.answer for more
     */
    public Placeholder(String text, int classID, int functionID) {
        this.functionID = functionID;
        this.text = text;
        this.classID = classID;
    }

    public String getText() {
        return text;
    }

    public void setText(String text) {
        this.text = text;
    }

    public int getClassID() {
        return classID;
    }

    public int getFunctionID() {
        return functionID;
    }
}