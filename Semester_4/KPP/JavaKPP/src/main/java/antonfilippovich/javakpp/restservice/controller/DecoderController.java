package antonfilippovich.javakpp.restservice.controller;

import antonfilippovich.javakpp.restservice.entity.Params;
import antonfilippovich.javakpp.restservice.entity.UnShifterEntity;
import antonfilippovich.javakpp.restservice.entity.ShifterEntity;
import antonfilippovich.javakpp.restservice.exceptions.InternalException;
import antonfilippovich.javakpp.restservice.logger.EventsLogger;
import antonfilippovich.javakpp.restservice.service.FuncShifterAPI;
import antonfilippovich.javakpp.restservice.service.ShifterAPI;

import antonfilippovich.javakpp.restservice.service.StatService;
import lombok.AllArgsConstructor;
import org.apache.logging.log4j.Level;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.HttpStatus;
import org.springframework.http.MediaType;
import org.springframework.web.bind.annotation.*;
import org.springframework.http.ResponseEntity;

import java.lang.reflect.Array;


@CrossOrigin(origins = "*", allowedHeaders = "*")
@AllArgsConstructor
@RestController
@RequestMapping("api/")
public class DecoderController {

    private final ShifterAPI shifterAPI;

    // StatisticsRepo statistics = new StatisticsRepo();
    CounterController NumberOfCalls = new CounterController();

    StatService statService = new StatService();

    @GetMapping(value = "text/shift", produces = MediaType.APPLICATION_JSON_VALUE)
    public ResponseEntity shiftText (@RequestParam(value = "text", defaultValue = "")String text){

        EventsLogger.Log(Level.INFO, "endpoint 'api/text/shift/' has been reached");

        NumberOfCalls.IncremetNumber();

        if(text.equals("")){
            EventsLogger.Log(Level.ERROR, "ERROR CODE 400: Empty input parameter");
            statService.increaseWrongRequests();
            return ResponseEntity.status(HttpStatus.BAD_REQUEST).body("ERROR CODE 400: Empty input param");
        } else if (text.equals("o")){
            EventsLogger.Log(Level.ERROR, "ERROR CODE 500: internal service exception");
            statService.increaseWrongRequests();
            throw new InternalException("ERROR CODE 500: internal service exception");
        }
        statService.addRoot(text.length());
        statService.increaseTotalRequests();

        // var params = new Params(text);
        // ShifterEntity shiftedResult = new ShifterEntity(text, shifterAPI.Shifter(params));
        ShifterEntity shiftedResult = new ShifterEntity(text, FuncShifterAPI.FuncShifter(text));
        return ResponseEntity.ok().body(shiftedResult);
    }



    @GetMapping(value = "text/unshift", produces = MediaType.APPLICATION_JSON_VALUE)
    public ResponseEntity unShiftText (@RequestParam(value = "text", defaultValue = "")String text){

        EventsLogger.Log(Level.INFO, "endpoint 'api/text/unshift/' has been reached");

        NumberOfCalls.IncremetNumber();

        if(text.equals("")){
            EventsLogger.Log(Level.ERROR, "ERROR CODE 400: Empty input parameter");
            statService.increaseWrongRequests();
            return ResponseEntity.status(HttpStatus.BAD_REQUEST).body("ERROR CODE 400: Empty input param");
        } else if (text.equals("o")){
            EventsLogger.Log(Level.ERROR, "ERROR CODE 500: internal service exception");
            statService.increaseWrongRequests();
            throw new InternalException("ERROR CODE 500: internal service exception");
        }
        // var params = new Params(text);
        // UnShifterEntity unShiftedResult = new UnShifterEntity(text, shifterAPI.UnShifter(params));

        statService.addRoot(text.length());
        statService.increaseTotalRequests();

        UnShifterEntity unShiftedResult = new UnShifterEntity(text, FuncShifterAPI.FuncUnShifter(text));
        return ResponseEntity.ok().body(unShiftedResult);
    }

    @PostMapping(value = "input",
            produces = MediaType.APPLICATION_JSON_VALUE,
            consumes = MediaType.APPLICATION_JSON_VALUE)
    public ResponseEntity filter(@RequestBody String[] arr) {
        EventsLogger.Log(Level.INFO, "input reached");
        return ResponseEntity.ok(FuncShifterAPI.FilterData(arr));
    }

}
