package cloudserver.model.daos;

import cloudserver.model.entities.Allergen;
import cloudserver.model.repos.AllergenRepository;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Component;

import java.util.List;
import java.util.NoSuchElementException;

@Component("allergenDAO")
public class AllergenDAO {

    private AllergenRepository repo;

    @Autowired
    public AllergenDAO(AllergenRepository repo) {
        this.repo = repo;
    }

    public Allergen create(Allergen allergen) {
        return repo.save(allergen);
    }

    public Allergen read(Long id) {
        return repo.findById(id).get();
    }

    public List<Allergen> read() {
        return repo.findAll();
    }

    public Allergen upsert(Allergen allergen) {
        repo.deleteById(allergen.getId());
        return repo.save(allergen);
    }

    public Allergen update(Allergen allergen) {
        if (repo.findById(allergen.getId()).isPresent()) {
            repo.deleteById(allergen.getId());
            return repo.save(allergen);
        }
        throw new NoSuchElementException("There is no Client with ID: " + allergen.getId());
    }

    public void delete(Long id) {
        repo.deleteById(id);
    }

    public void delete() {
        repo.deleteAll();
    }
}
