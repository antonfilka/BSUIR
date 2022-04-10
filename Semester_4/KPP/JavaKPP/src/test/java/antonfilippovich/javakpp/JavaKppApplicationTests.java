package antonfilippovich.javakpp;

import antonfilippovich.javakpp.restservice.entity.Params;
import antonfilippovich.javakpp.restservice.service.ShifterAPI;
import org.junit.jupiter.api.Test;
import org.springframework.boot.test.context.SpringBootTest;

@SpringBootTest
class JavaKppApplicationTests {

    private final ShifterAPI shifterAPI;

    JavaKppApplicationTests(ShifterAPI shifterAPI) {
        this.shifterAPI = shifterAPI;
    }

    @Test
    void ShifterABC() {
        Params param = new Params("abc");
        String result1 = shifterAPI.Shifter(param);
        String expected = "fgh";
        assert (result1.equals(expected));
    }

    @Test
    void ShifterWord() {
        Params param = new Params("hello");
        String result1 = shifterAPI.Shifter(param);
        String expected = "mjqqt";
        assert (result1.equals(expected));
    }

    @Test
    void ShifterWithNumber() {
        Params param = new Params("world123");
        String result1 = shifterAPI.Shifter(param);
        String expected = "|twqi678";
        assert (result1.equals(expected));
    }

    @Test
    void UnShifterWord() {
        Params param = new Params("hello");
        String result1 = shifterAPI.UnShifter(param);
        String expected = "c`ggj";
        assert (result1.equals(expected));
    }

}
