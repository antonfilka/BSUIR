package antonfilippovich.javakpp.restservice.Statistics;

import lombok.Getter;
import org.springframework.stereotype.Component;

@Component
@Getter
public class Statistics {
    public Integer totalRequests = 0;
    public Integer wrongRequests = 0;
    public Integer min = 0;
    public Integer max = 0;
    public Integer mostCommon = 0;
}


