package main_package;

import java.util.HashMap;

/**
 * Class responsible for all shortcut-like transformations.
 */
public class ShortcutTransformation extends TransformationDecorator {

    /**
     * Constructor of shortcut transformation class.
     * @param t decorating transformation
     * @param index Index of transformation performed by this object
     */
    public ShortcutTransformation(Transformation t, int index){
        super(t, index);
    }

    /**
     * Predefined hashmap containing word - shortcut collocation.
     */
    private static final HashMap<String,String> shortcutsWord = new HashMap<String, String>() {{
        put("np.", "na przykład ");
        put("Np.", "Na przykład ");
        put("NP.", "Na Przykład ");
        put("itd.", "i tym podobne ");
        put("Itd.", "I Tym Podobne ");
        put("ITD.", "I TYM PODOBNE ");
        put("dr", "doktor ");
        put("Dr", "Doktor ");
        put("DR", "DOKTOR ");
        put("prof.", "profesor ");
        put("Prof.", "Profesor ");
        put("PROF.", "PROFESOR ");
    }};

    /**
     * Predefined hashmap containing shortcut - word collocation
     */
    private static final HashMap<String,String> wordShortcuts = new HashMap<String, String>() {{
        put("na przykład", "np. ");
        put("i tym podobne", "itp. ");
        put("między innymi", "m.in. ");
    }};

    /**
     * Predefined hashmap containing char - latex notation collocation.
     */
    private static final HashMap<String,String> latex = new HashMap<String, String>() {{
        put("&", "\\&");
        put("$", "\\$");
    }};
    
    /**
     * Function to change format to Latex
     * @param text String to transformation
     * @return text after transformation
     */
    private static String toLatex (String text) {
        String [] result;
        String finaly = "";
        result = text.split(" ");

        for (int i = 0; i < result.length; i++) {
            for (int j = 0; j < result[i].length(); j++)
                switch (result[i].charAt(j)) {
                    case '&':
                        finaly += latex.get("&");
                        break;

                    case '$':
                        finaly += latex.get("$");
                        break;

                    default:
                        finaly += result[i].charAt(j);
                }

            if (i != result.length - 1)
                finaly += " ";
        }
        return finaly;
    }

    /**
     * Function to reduce words to shortcuts
     * @param text String to transformation
     * @return text after transformation
     */
    static String wordToShortcut (String text) {
        String[] result;
        String finaly = "";
        result = text.split(" ");

        for (int i = 0; i < result.length; i++) {           //zakladamy, ze nie ma skrotu jednowyrazowego
            if (i < result.length - 1)
                switch ((result[i]).toLowerCase() + (result[i+1]).toLowerCase() ) {
                    case "itym":
                        if (i != result.length - 2 && (result[i+2]).toLowerCase().equals("podobne"))
                            finaly += wordShortcuts.get("i tym podobne");
                        i += 2;
                        break;
                    case "międzyinnymi":
                        finaly += wordShortcuts.get("między innymi");
                        i++;
                        break;
                    case "naprzykład":
                        finaly += wordShortcuts.get("na przykład");
                        i++;
                        break;
                    default:
                        finaly += result[i] + " ";
                        break;
                }
            else
                finaly += result[i] + " ";
        }

        //delete end space
        if (finaly.length() >= 1)
            finaly = finaly.substring(0, finaly.length()-1);

        return finaly;
    }

    /**
     * Function to expand shortcuts
     * @param text String to transformation
     * @return text after transformation
     */
    private static String shortcutToWord (String text) {
        String [] result;
        String finaly = "", pom;
        result = text.split(" ");

        for (int i = 0; i < result.length; i++) {
            pom = shortcutsWord.get(result[i]);
            if (pom != null)
                finaly += pom;
            else
                finaly += result[i] + " ";
        }

        //delete end space
        if (finaly.length() >= 1)
            finaly = finaly.substring(0, finaly.length()-1);

        return finaly;
    }

    /**
     * Main function that depends on given index returns:
     * 0: word to shortcut
     * 1: shortcut to word
     * 2: to Latex format
     * @param text custom String given by user
     * @return text after transformation
     */
    @Override
    public String transform(String text)
    {
        String result;
        switch (super.getTransformationIndex()) {
            case 0:
                result = wordToShortcut(text);
                break;
            case 1:
                result = shortcutToWord(text);
                break;
            case 2:
                result = toLatex(text);
                break;
            default:
                result = "Uratowałeś mnie! Ale Twoja funkcja jest w innym zamku!";
                break;
        }
        return super.transform(result);
    }
}
