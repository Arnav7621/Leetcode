import pandas as pd

def duplicate_emails(person: pd.DataFrame) -> pd.DataFrame:
    duplicates = person[person["email"].duplicated()]["email"].drop_duplicates()
    
    return duplicates.to_frame(name="Email")