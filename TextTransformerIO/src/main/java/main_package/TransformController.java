package main_package;

import com.fasterxml.jackson.databind.ObjectMapper;
import org.springframework.web.bind.annotation.*;

import java.io.IOException;

/**
 * Class serving as a REST controller for TextTransformer's Rest API
 */
@RestController
public class TransformController
{
    /**
     * Function collecting PUT Requests from clients.
     * Prepares and sends data in JSON format to the client.
     *
     * @param payload - Body of the PUT request formatted in JSON with fields as follows:
     *     - text - Text (in string) to be transformed
     *     - classID - ID number of the class used to transform the text (see below)
     *     - functionID - ID number of the function from given class which performs the transformation (see below)
     *
     *     Classes and function IDs:
     *     Class ID: 1 - Number Transformation
     *        Function ID: any, since that class performs only one transformation
     *        (transform number to its string equivalent in Polish)
     *
     *     Class ID: 2 - Shortcut Transformation
     *        Function ID:
     *           0 - Transform whole words to its shortcuts, ie. Na przykład - Np.
     *           1 - Transform shortcuts to whole words, ie. Np. - Na przykład.
     *           2 - Transform particular characters to the LaTeX format.
     *
     *     Class ID: 3 - Text Transformation
     *         Function ID:
     *           0 - Transform text to uppercase
     *           1 - Transform text to lowercase
     *           2 - Invert the whole text
     *           3 - Capitalize first letters in each word
     *           4 - Remove repetitive words in text
     *
     *     Class ID: 4 - Cipher Transformation
     *         Function ID:
     *           0 - Transform text with Caesar Code
     *           1 - Permutation
     *
     * @return Sends object containing transformed text along with class and function ID's used in transformation
     * in JSON format as a response from the server.
     */
    @CrossOrigin
    @RequestMapping(method = RequestMethod.PUT)
    public Placeholder answer(@RequestBody String payload)
    {
        ObjectMapper mapper = new ObjectMapper();

        Transformation t = new SimpleTransformation();

        try
        {
            Placeholder pl = mapper.readValue(payload, Placeholder.class);

            // Creating proper object to transform:

            switch(pl.getClassID()) {
                case 1: {
                    t = new NumberTransformation(t, pl.getFunctionID());
                    break;
                }
                case 2: {
                    t = new ShortcutTransformation(t, pl.getFunctionID());
                    break;
                }
                case 3: {
                    t = new TextTransformation(t, pl.getFunctionID());
                    break;
                }
                case 4: {
                    t = new CipherTransformation(t, pl.getFunctionID());
                    break;
                }
                default: {
                    t = new SimpleTransformation();
                    break;

                }
            }

            String text = t.transform(pl.getText());

            return new Placeholder(text, pl.getClassID(), pl.getFunctionID());
        }
        catch (IOException e)
        {
            System.out.println("Internal server error - popsuło się");
            e.printStackTrace();
            return new Placeholder("Error", -1, -1);
        }
    }
}
