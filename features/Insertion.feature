Feature: Insertion

  Scenario: inserting things into the file and save it
     Given opened test.txt
      When we insert words, numbers and ENTERs
      Then the changes will be applied to test.txt
