package antonfilippovich.javakpp.restservice.controller;
import antonfilippovich.javakpp.restservice.Statistics.Statistics;
import antonfilippovich.javakpp.restservice.service.StatService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.HttpStatus;
import org.springframework.http.MediaType;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

@RestController
@RequestMapping("/statistics")
public class StatisticController {
    private  StatService statProv;

    @Autowired
    public void StatController(StatService statProv) {
        this.statProv = statProv;
    }

    @GetMapping(value = "/stat", produces = MediaType.APPLICATION_JSON_VALUE)
    public ResponseEntity stat (){
        statProv.calculate();
        return ResponseEntity.ok().body(statProv.getStats());
    }
}


