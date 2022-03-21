export const removeNumbersFromString = (string) => string.replace(/[0-9]/g, '');

export const capitalize = (s) => {
    if (typeof s !== 'string') return ''
    return s.charAt(0).toUpperCase() + s.slice(1)
}

export const maritalCodeToString = (code) => {
    switch(code.toUpperCase()){
        case 'A':
            return "Annulled";
        case 'D':
            return "Divorced";
        case 'I':
            return `Interlocutory`;
        case 'L':
            return `Legally separated`;
        case `M`:
            return "Married"
        case `C`:
            return `Common Law`;
        case `P`:
            return 'Polygamous';
        case 'T':
            return 'Domestic partner';
        case `U`:
            return `Unmarried`;
        case `W`:
            return `Widowed`;
        default:
            return "Never Married";
    }
}

export const dateToString = date => {
    const dateTimeFormat = new Intl.DateTimeFormat('en-US', { 
        year: 'numeric',
        month: 'short',
        day: '2-digit',
        hour: '2-digit',
        hour12: false,
        minute: '2-digit'
    });
    
    const [
        { value: month },,
        { value: day },,
        { value: year }] = dateTimeFormat.formatToParts(date);
    const formattedDate = `${day} ${month} ${year}`;
    return formattedDate;
}