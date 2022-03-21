package main_package;

/**
 * Interface which define main transform functionality.
 */
public interface Transformation {
    /**
     * Main function that will transform text on (index) transformation of a class.
     * @param text custom String given by user
     * @return text after transformation
     */
    public String transform(String text);
}
