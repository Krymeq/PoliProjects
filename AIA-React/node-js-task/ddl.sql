CREATE TABLE items (
    id INT NOT NULL AUTO_INCREMENT,
    name VARCHAR(100) NOT NULL,
    quantity INT NOT NULL,
    price FLOAT(2) NOT NULL,
    PRIMARY KEY(id)
);

INSERT INTO items(name, quantity, price) VALUES
    ('Gibson Les Paul', 5, 7499.99),
    ('Fender Stratocaster', 8, 3599.99),
    ('Schecter Omen', 11, 1199.99),
    ('Ibanez RG421AHM', 3, 1899.99);
