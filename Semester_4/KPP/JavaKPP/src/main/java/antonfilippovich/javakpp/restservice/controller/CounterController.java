package antonfilippovich.javakpp.restservice.controller;
import antonfilippovich.javakpp.restservice.logger.EventsLogger;
import org.apache.logging.log4j.Level;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

@RestController
@RequestMapping("api/")
public class CounterController {

    static int NumberOfRequests = 0;

    synchronized public void IncremetNumber(){
        NumberOfRequests++;
        EventsLogger.Log(Level.INFO, "Counter increment!");
    }

    @GetMapping(value = "/counter")
    synchronized public ResponseEntity counter (){
        return ResponseEntity.ok().body(NumberOfRequests);
    }


}
