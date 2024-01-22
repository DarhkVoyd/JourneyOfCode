use std::collections::HashMap;

#[derive(Debug)]
pub struct QueryParams<'a> {
    data: HashMap<&'a str, Value<'a>>,
}

#[derive(Debug)]
pub enum Value<'a> {
    Single(&'a str),
    Multiple(Vec<&'a str>),
}

impl<'a> QueryParams<'a> {
    fn get(&self, key: &str) -> Option<&Value> {
        self.data.get(key)
    }
}

impl<'a> From<&'a str> for QueryParams<'a> {
    fn from(str: &'a str) -> QueryParams<'a> {
        let mut data = HashMap::new();

        for param in str.split('&') {
            let mut key = param;
            let mut val = "";
            if let Some(idx) = param.find('=') {
                key = &param[..idx];
                val = &param[idx + 1..];
            }

            data.entry(key).and_modify(|entry| match entry {
                Value::Single(prev_entry) => {
                    let new_entry = vec![prev_entry, val];
                    *entry = Value::Multiple(new_entry);
                },
                Value::Multiple(prev_entry) => prev_entry.push(val),
            }).or_insert(Value::Single(val));
        }
        QueryParams { data }
    }
}
