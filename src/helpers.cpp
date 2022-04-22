
// < All the variables will be stored here
unordered_map<string, string> var_table; 
// All the variables will be stored here >


string tabs(int t){
    // To be used when printing the flow in a 'beautiful' way

    string r = "";
    while(t--)r+="\t";
    return r;
}

bool isTruthy(string value){
    // Truthiness of the string

    if (value[0]=='\''){return value.length() > 2;}
    return stof(value)!= 0;
}

bool mapContainsKey(string key){
    // Check for the presence of a key in the var table

    if (var_table.find(key) == var_table.end()) return false;
    return true;
}
