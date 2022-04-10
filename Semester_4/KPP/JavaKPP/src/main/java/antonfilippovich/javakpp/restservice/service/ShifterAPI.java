package antonfilippovich.javakpp.restservice.service;


import antonfilippovich.javakpp.restservice.cache.Cache;
import antonfilippovich.javakpp.restservice.entity.Params;
import antonfilippovich.javakpp.restservice.logger.EventsLogger;
import lombok.AllArgsConstructor;
import org.apache.logging.log4j.Level;
import org.springframework.stereotype.Service;

@AllArgsConstructor
@Service
public class ShifterAPI {

    private Cache cache;
    private static final int shiftValue = 5;


    public  String Shifter(Params param){

        if (cache.find(param) != null) {
            EventsLogger.Log(Level.INFO, "Response is already in cache!");
            return cache.find(param);
        }

        StringBuilder resultString = new StringBuilder();

        for (char c : param.text().toCharArray()){
            resultString.append((char) ((int) c + shiftValue));
        }
        EventsLogger.Log(Level.DEBUG, "Text has been Shifted successfully");
        cache.add(param, resultString.toString());
        return resultString.toString();
    }

    public  String UnShifter(Params param){

            StringBuilder resultString = new StringBuilder();
            for (char c : param.text().toCharArray()){
                resultString.append((char) ((int) c - shiftValue));
            }
            EventsLogger.Log(Level.DEBUG, "Text has been unShifted successfully");

            return resultString.toString();
    }
}
