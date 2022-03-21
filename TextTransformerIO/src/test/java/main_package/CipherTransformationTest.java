package main_package;

import org.junit.Assert;
import org.junit.Before;
import org.junit.Test;

public class CipherTransformationTest {
    private Transformation t;

    @Before
    public void setup() {
        t = new SimpleTransformation();
    }

    @Test
    public void caesarCodeTest() {
        Transformation tx = new CipherTransformation(this.t, 0);

        String[] predicted = new String[3];
        String[] result =  {"BUHEŁI", "nryhn", "Ćńć óć śwć-012"};

        predicted[0] = tx.transform("ŹREBIĘ");
        predicted[1] = tx.transform("kotek");
        predicted[2] = tx.transform("Ala ma psa-012");

        Assert.assertArrayEquals(result, predicted);
    }
}
