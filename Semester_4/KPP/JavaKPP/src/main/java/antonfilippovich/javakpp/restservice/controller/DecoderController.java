package antonfilippovich.javakpp.restservice.controller;

import antonfilippovich.javakpp.restservice.entity.Params;
import antonfilippovich.javakpp.restservice.entity.UnShifterEntity;
import antonfilippovich.javakpp.restservice.entity.ShifterEntity;
import antonfilippovich.javakpp.restservice.exceptions.InternalException;
import antonfilippovich.javakpp.restservice.logger.EventsLogger;
import antonfilippovich.javakpp.restservice.service.ShifterAPI;

import lombok.AllArgsConstructor;
import org.apache.logging.log4j.Level;
import org.springframework.http.HttpStatus;
import org.springframework.http.MediaType;
import org.springframework.web.bind.annotation.*;
import org.springframework.http.ResponseEntity;


@CrossOrigin(origins = "*", allowedHeaders = "*")
@AllArgsConstructor
@RestController
@RequestMapping("api/")
public class DecoderController {

    private final ShifterAPI shifterAPI;
    CounterController NumberOfCalls = new CounterController();

    @GetMapping(value = "text/shift", produces = MediaType.APPLICATION_JSON_VALUE)
    public ResponseEntity shiftText (@RequestParam(value = "text", defaultValue = "")String text){

        EventsLogger.Log(Level.INFO, "endpoint 'api/text/shift/' has been reached");

        NumberOfCalls.IncremetNumber();

        if(text.equals("")){
            EventsLogger.Log(Level.ERROR, "ERROR CODE 400: Empty input parameter");
            return ResponseEntity.status(HttpStatus.BAD_REQUEST).body("ERROR CODE 400: Empty input param");
        } else if (text.equals("o")){
            EventsLogger.Log(Level.ERROR, "ERROR CODE 500: internal service exception");
            throw new InternalException("ERROR CODE 500: internal service exception");
        }

        var params = new Params(text);
        ShifterEntity shiftedResult = new ShifterEntity(text, shifterAPI.Shifter(params));
        return ResponseEntity.ok().body(shiftedResult);
    }



    @GetMapping(value = "text/unshift", produces = MediaType.APPLICATION_JSON_VALUE)
    public ResponseEntity unShiftText (@RequestParam(value = "text", defaultValue = "")String text){

        EventsLogger.Log(Level.INFO, "endpoint 'api/text/unshift/' has been reached");

        NumberOfCalls.IncremetNumber();

        if(text.equals("")){
            EventsLogger.Log(Level.ERROR, "ERROR CODE 400: Empty input parameter");
            return ResponseEntity.status(HttpStatus.BAD_REQUEST).body("ERROR CODE 400: Empty input param");
        } else if (text.equals("o")){
            EventsLogger.Log(Level.ERROR, "ERROR CODE 500: internal service exception");
            throw new InternalException("ERROR CODE 500: internal service exception");
        }
        var params = new Params(text);
        UnShifterEntity unShiftedResult = new UnShifterEntity(text, shifterAPI.UnShifter(params));
        return ResponseEntity.ok().body(unShiftedResult);
    }

}
