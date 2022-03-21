package main_package;
import java.util.HashMap;

import static java.lang.Math.abs;

/**
 * Class responsible for all numerical transformations.
 */
class NumberTransformation extends TransformationDecorator {

    /**
     * Constructor of number transformation class.
     * @param t decorating transformation
     * @param index Index of transformation performed by this object
     */
    public NumberTransformation(Transformation t, int index){
        super(t, index);
    }

    /**
     * Hashmap with predefined specific word-numbers.
     */
    private static final HashMap<Integer,String> numbers = new HashMap<Integer, String>() {{
        put(1,"jeden");
        put(2,"dwa");
        put(3,"trzy");
        put(4,"cztery");
        put(5,"pięć");
        put(6,"sześć");
        put(7,"siedem");
        put(8,"osiem");
        put(9,"dziewięć");
        put(20,"dwadzieścia");
        put(30,"trzydzieści");
        put(40,"czterdzieści");
        put(200,"dwieście");

        put(0,"zero");
        put(10,"dziesięć");
        put(100,"sto");
    }};

    /**
     * Function converting a given number into words.
     * @param x number to translate
     * @return text
     */
    private static String integers(Integer x) {

        int setki = x / 100;
        int dziesiatki = (x - setki * 100) / 10;
        int jednosci = (x - setki * 100 - dziesiatki * 10);

        String text = "";
        switch (setki) {
            case 0:
                break;
            case 1:
                text += numbers.get(100);
                break;
            case 2:
                text += numbers.get(200);
                break;
            case 3:
            case 4:
                text += numbers.get(setki);
                text += "sta";
                break;
            case 5:
            case 6:
            case 7:
            case 8:
            case 9:
                text += numbers.get(setki);
                text += "set";
                break;
            default:
                return "Liczba poza zakresem";
        }

        if (setki != 0)
            text += " ";

        switch (dziesiatki) {
            case 0:
                // zero
                break;
            case 1:
                // wyjątki 10-19
                switch(jednosci) {
                    case 0:
                        text += numbers.get(10);
                        break;
                    case 1:
                        text += numbers.get(jednosci).replace("n", "");
                        break;
                    case 2: // + naście
                    case 3: // + naście
                    case 7:
                    case 8:
                        text += numbers.get(jednosci);
                        break;
                    case 4: // -y
                        text += numbers.get(jednosci).replace("y","");
                        break;
                    case 5: // ć = t
                    case 9:
                        text += numbers.get(jednosci).replace("ć","t");
                        break;
                    case 6: // -ć, ś = s
                        String temp = numbers.get(jednosci).replace("ć", "");
                        text += numbers.get(jednosci).replace("ś", "s");
                        break;
                    default:
                        return "Warość poza zakresem";
                }
                if (jednosci != 0)
                    text += "naście";
                return text;
            case 2:
                text += numbers.get(20);
                break;
            case 3:
                text += numbers.get(30);
                break;
            case 4:
                text += numbers.get(40);
                break;
            case 5:
            case 6:
            case 7:
            case 8:
            case 9:
                text += numbers.get(dziesiatki);
                text += "dziesiąt";
                break;
            default:
                return "Liczba poza zakresem";
        }
        if (dziesiatki != 0 && jednosci != 0)
            text += " ";

        if (jednosci != 0 || text.equals(""))
            text += numbers.get(jednosci);
        return text;
    }

    /**
     * Function converting a given hundredths into words.
     * @param x number
     * @return text
     */
    private static String hundredths(Double x) {
        String text = "";
        x -= x.intValue();
        x *= 100;
        int dziesietne = x.intValue() / 10;
        int setne = x.intValue() % 10;

        text = integers(x.intValue());

        /*
        1 -> jedna setna
        2 -> dwie setne
        3 -> trzy setne
        4 -> cztery setne
        5,6,7,8,9,0 -> pięć setnych
        x2 -> x dwie setne
        x3 -> x trzy setne
         */
        if (dziesietne == 0 && setne == 0)
            return "";
        else if (dziesietne == 0 && setne == 1)
            text = text.replace(numbers.get(setne), "jedna setna");
        else if (setne == 2 || setne == 3 || setne == 4) {
            text = text.replace(numbers.get(2), "dwie");
            text += " setne";
        }
        else
            text += " setnych";

        return text;
    }

    /**
     * Function transforming Number to text.
     * Overloaded with Integer.
     * @param number variable to transform
     * @return string value of a given number
     */
    private static String transformNumber(Integer number) {
        return integers(number);
    }

    /**
     * Function transforming Number to text.
     * Overloaded with Double.
     * @param number variable to transform
     * @return string value of a given number
     */
    private String transformNumber(Double number) {
        String text = integers(number.intValue());
        String temp = hundredths(number);
        if (!temp.equals("")) {
            text += (" i " + temp);
            if (abs(number.intValue()) < 1){
                text = temp;
            }
        }

        return text;
    };

    /**
     * Public function that transforms every number in text to its text format.
     * Override from Transformation - it also takes into consideration previously
     * decorated transforms
     * @param text custom String given by user
     * @return text after transformation
     */
    @Override
    public String transform(String text) {
        String[] words = text.split(" ");
        for (int i = 0; i < words.length; i++) {
            try {
                words[i] = transformNumber(Double.parseDouble(words[i]));
            } catch (NumberFormatException | NullPointerException nfe) {
                continue;
            }
        }
        String result = String.join(" ", words);
        return super.transform(result);
    }
}
