package cloudserver.model.jsonparsers;

import com.fasterxml.jackson.databind.ObjectMapper;
import org.springframework.stereotype.Service;


@Service("JSONParser")
public class JSONToObjectParser implements ParserJSON {
    @Override
    public Object parse(String json, Class clazz) {
        ObjectMapper objectMapper = new ObjectMapper();
        try {
            return objectMapper.readValue(json, clazz);
        } catch (Exception e) {
            e.printStackTrace();
            return null;
        }
    }
}
