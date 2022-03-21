package main_package;

/**
 * Abstract decorator class, which takes different transformations.
 */
public abstract class TransformationDecorator implements Transformation {
    private Transformation decoratedTransformation;
    private int transformationIndex;

    /**
     * Constructor of abstract transformation decorator.
     * @param t decorated transformation
     * @param idx Index of transformation to be performed by this object
     */
    public TransformationDecorator(Transformation t, int idx) {
        this.decoratedTransformation = t;
        this.transformationIndex = idx;
    }

    /**
     * Transforming function which takes text and index of transformation.
     * Runs function of actual decorated object.
     * @param text given string by user
     * @return text after transformation
     */
    @Override
    public String transform(String text)
    {
        return decoratedTransformation.transform(text);
    }

    public int getTransformationIndex() {
        return transformationIndex;
    }
}
