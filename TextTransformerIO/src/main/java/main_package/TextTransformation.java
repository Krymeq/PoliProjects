package main_package;

import java.util.Arrays;

/**
 * Class providing a variety of text-based transformations, eg. inversion.
 */
public class TextTransformation extends TransformationDecorator {

    /**
     * Constructor of text transformation class.
     * @param t Decorated transformation
     * @param index Index of transformation performed by this object
     */
    public TextTransformation(Transformation t, int index) {
        super(t, index);
    }

    /**
     * Function that converts text to UPPER text.
     * @param text given string by user
     * @return text after transformation
     */
    private static String upper(String text) {
        return text.toUpperCase();
    }

    /**
     * Function that converts text to lower text.
     * @param text given string by user
     * @return text after transformation
     */
    private static String lower(String text) {
        return text.toLowerCase();
    }

    /**
     * Function that converts whole sentence to Capital words.
     * @param text given string by user
     * @return text after transformation
     */
    private static String capital(String text) {
        String[] temp = text.split(" ");
        StringBuilder result = new StringBuilder();

        for (String i: temp) {
            result.append(i.substring(0,1).toUpperCase() + i.substring(1)).append(" ");
        }

        return result.toString();
    }

    /**
     * Function that inverts a word having the same Capital letters.
     * @param text given string by user
     * @return text after transformation
     */
    private static String inverse(String text) {
        String[] dividedText = text.split(" ");
        String[] inverted = new String[dividedText.length];

        for (int j = 0; j < dividedText.length; j++) {
            String[] word = dividedText[j].split("");
            String[] result = new String[word.length];

            for (int i = 0; i < word.length; i++) {
                if (Character.isUpperCase(word[i].charAt(0)))
                    result[i] = upper(word[word.length - 1 - i]);
                else
                    result[i] = lower(word[word.length - 1 - i]);
            };

            inverted[j] = String.join("", result);
        }

        return String.join(" ", inverted);
    }
    
    /**
     * Function that deletes repetitive word.
     * @param text given string by user
     * @return text after transformation
     */
    protected static String deleteSample (String text) {
        String [] result;
        String finaly = "";
        result = text.split(" ");

        for (int i = 1; i < result.length; i++)         //usun spacje obok sb
            if (result[i].equals(""))
                result[i] = result[i - 1];

        for (int i = 0; i < result.length; i++)         //przejdz po wszystkich wyrazach i sprawdz, czy kolejny nie jest taki sam
            if (i != result.length - 1 && result[i].equals(result[i + 1]))
                finaly += "";                              //usun z tablicy - zamien na pusty string
            else if (i != result.length-1)
                finaly += result[i] + " ";
            else
                finaly += result[i];

        return finaly;
    }

    /**
     * Main function that depends on given index returns:
     * 0: upper text
     * 1: lower text
     * 2: inverse text
     * 3: capital letters
     * 4: without repetitions
     * @param text custom String given by user
     * @return text after transformation
     */
    public String transform(String text) {
        String result;
        switch (super.getTransformationIndex()) {
            case 0:
                result = upper(text);
                break;
            case 1:
                result = lower(text);
                break;
            case 2:
                result = inverse(text);
                break;
            case 3:
                result = capital(text);
                break;
            case 4:
                result = deleteSample(text);
                break;
            default:
                result = "Uratowałeś mnie! Ale Twoja funkcja jest w innym zamku!";
        }
        return super.transform(result);
    }
}
