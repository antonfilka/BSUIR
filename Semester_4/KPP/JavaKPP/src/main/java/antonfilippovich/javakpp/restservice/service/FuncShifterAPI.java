package antonfilippovich.javakpp.restservice.service;

import antonfilippovich.javakpp.restservice.logger.EventsLogger;
import org.apache.logging.log4j.Level;
import java.util.stream.Collector;
import java.util.stream.IntStream;
import java.util.stream.Stream;

public class FuncShifterAPI {

    public static String FuncShifter (String text){
        IntStream characterStream = text.chars();
        EventsLogger.Log(Level.DEBUG, "Text is being shifted");
        return characterStream.map(item -> item + 1).mapToObj(c -> (char) c).collect(Collector.of(
                StringBuilder::new,
                StringBuilder::append,
                StringBuilder::append,
                StringBuilder::toString));
    }

    public static String FuncUnShifter (String text){
        IntStream characterStream = text.chars();
        EventsLogger.Log(Level.DEBUG, "Text is being unShifted");
        return characterStream.map(item -> item - 1).mapToObj(c -> (char) c).collect(Collector.of(
                StringBuilder::new,
                StringBuilder::append,
                StringBuilder::append,
                StringBuilder::toString));
    }

    public static int[] FilterData (String[] arr){
        EventsLogger.Log(Level.INFO, "Filtering");
        IntStream stream = Stream.of(arr).mapToInt(Integer::parseInt);
        return stream.filter(i -> i < 100).toArray();
    }
}
