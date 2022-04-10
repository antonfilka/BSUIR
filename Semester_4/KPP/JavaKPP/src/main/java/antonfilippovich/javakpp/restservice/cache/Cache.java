package antonfilippovich.javakpp.restservice.cache;

import antonfilippovich.javakpp.restservice.entity.Params;
import antonfilippovich.javakpp.restservice.logger.EventsLogger;
import org.apache.logging.log4j.Level;
import org.springframework.stereotype.Component;
import java.util.HashMap;

@Component("Cache")
public class Cache {

    private final HashMap<Params, String> solutions = new HashMap<>();

    public void add(Params params, String root) {
        solutions.put(params, root);
        EventsLogger.Log(Level.INFO,  "Value " + params + "@" + root + " added to cache!");
    }

    public String find(Params params) {
        var result = solutions.get(params);
        if (result != null) EventsLogger.Log(Level.INFO,  "Value " + params  + "was taken from cache!");
        return result;
    }
}
