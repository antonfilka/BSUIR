package antonfilippovich.javakpp.restservice;

import antonfilippovich.javakpp.restservice.cache.Cache;
import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;
import org.springframework.context.annotation.Scope;

@Configuration
public class SpringConfiguration {

    @Bean("cache")
    @Scope(value = "singleton")
    Cache cache(){
        return new Cache();
    }
}
