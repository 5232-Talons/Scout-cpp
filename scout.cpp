/**************************************************************************************
Implementation of a basic routine to caluclate teams overall avg score & avg note score.


***************************************************************************************/

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <math.h>
#include <iomanip>
#include "./util/csv.hpp"

using namespace std;

/*
This is to be depreciated

Keep it in for a few more iterations incase an issue arises with CSVReader.
*/
void csv_to_matrix(const string &, vector<vector<int>> &);

int main()
{
    char ch_has_header{'n'};
    string filename = "robot_scores.csv"; // Provide the path to your CSV file -- This will serve as a default name as well.

    cout << "Enter filename to load: ";
    cin >> filename;
    cout << '\n';

    cout << "Does this CSV file have a header (y/n): ";
    cin >> ch_has_header;
    cout << '\n';

    auto result = CSVReader(filename).ParseCSV((ch_has_header == 'y' ? true : false)).GetResults();

    vector<vector<int>> matrix{};
    for (const auto &[key, value] : result)
    {
        for (const auto &row : value)
            matrix.push_back(row);
    }

    // TODO: Move this to a Map (ordered or unorderd doesn't matter)
    const vector<int> team_numbers = {
        1714, 1716, 1792, 1806, 2039, 2062, 2129, 2169, 2175, 2227,
        2264, 2472, 2491, 2501, 2512, 2574, 2846, 2855, 2987, 3023,
        3082, 3100, 3130, 3206, 3212, 3297, 3418, 3883, 4166, 4182,
        4229, 4230, 4623, 4703, 4786, 5232, 5271, 5275, 5339, 5720,
        5913, 6044, 6045, 6047, 6132, 6147, 6419, 6574, 6758, 7273,
        7530, 7619, 8122, 8700, 8803};

    vector<double> avg_score(team_numbers.size(), 0);       // Initialize avg score vector, filled with zeroes
    vector<double> notes_avg_score(team_numbers.size(), 0); // Initialize notes avg score vector, filled with zeroes
    vector<double> match_score(matrix.size(), 0);
    size_t team_number{};
    int count{};
    vector<double> stdev(team_numbers.size(), 0);        // Initialize notes avg score vector, filled with zeroes
    vector<double> driver_score(team_numbers.size(), 0); // Initialize driver score vector, filled with zeroes
    vector<double> climbing_score(team_numbers.size(), 0);
    vector<double> human_score(team_numbers.size(), 0);
    vector<double> match_count(team_numbers.size(), 0);

    // TOOD: These scores should be moved to a struct or class, this would also support qualitative data as well then.
    for (size_t i = 0; i < team_numbers.size(); ++i)
    {
        team_number = team_numbers[i];
        for (size_t j = 0; j < matrix.size(); ++j)
        {
            if (matrix[j][0] == team_number)
            {
                match_score[j] = matrix[j][1] + matrix[j][3] + 2 * matrix[j][4] + matrix[j][5] * 3 + matrix[j][6] * 5;
                avg_score[i] += match_score[j];
                notes_avg_score[i] += matrix[j][1] + matrix[j][3] + 2 * matrix[j][4];
                count++;
            }
        }
        // Calculate average score after all matches of the team are accumulated
        if (count != 0)
        {
            avg_score[i] = avg_score[i] / count;
            notes_avg_score[i] = notes_avg_score[i] / count;
            match_count[i] = count;
        }
        // Reset count for the next team
        count = 0;
    }

    for (size_t i = 0; i < team_numbers.size(); ++i)
    {
        team_number = team_numbers[i];
        for (size_t j = 0; j < matrix.size(); ++j)
        {
            if (matrix[j][0] == team_number)
            {
                stdev[i] += pow(avg_score[i] - match_score[j], 2);
                count++;
            }
        }
        // Calculate average score after all matches of the team are accumulated
        if (count != 0)
        {
            stdev[i] = sqrt(stdev[i] / count);
        }
        // Reset count for the next team
        count = 0;
    }

    for (size_t i = 0; i < team_numbers.size(); ++i)
    {
        for (size_t j = 0; j < matrix.size(); ++j)
        {
            if (matrix[j][0] == team_number)
            {
                driver_score[i] += matrix[j][7];
                count++;
            }
        }
        // Calculate averagescore after all matches of the team are accumulated
        if (count != 0)
        {
            driver_score[i] = driver_score[i] / count;
        }

        // Reset count for the next team
        count = 0;
    }

    for (size_t i = 0; i < team_numbers.size(); ++i)
    {
        for (size_t j = 0; j < matrix.size(); ++j)
        {
            if (matrix[j][0] == team_numbers[i])
            { // Fix this line
                climbing_score[i] += matrix[j][5];
                count++;
            }
        }

        // Calculate average score after all matches of the team are accumulated
        if (count != 0)
        {
            climbing_score[i] = climbing_score[i] / count; // Fix this line
        }

        // Reset count for the next team
        count = 0;
    }

    for (size_t i = 0; i < team_numbers.size(); ++i)
    {
        for (size_t j = 0; j < matrix.size(); ++j)
        {
            if (matrix[j][0] == team_number)
            {
                human_score[i] += matrix[j][8];
                count++;
            }
        }

        // Calculate averagescore after all matches of the team are accumulated
        if (count != 0)
        {
            human_score[i] = human_score[i] / count;
        }

        // Reset count for the next team
        count = 0;
    }

    int choice{}, team{}, blue1{}, blue2{}, blue3{}, red1{}, red2{}, red3{}, bluetot{}, redtot{}, blue1_score{}, blue2_score{}, blue3_score{}, red1_score{}, red2_score{}, red3_score{};

    cout << "****************************************" << endl;
    cout << "  Welcome to 5232's Scouting Analytics" << endl;
    cout << "****************************************" << endl;

    cout << endl;

    int exit_prog{6};
    while (choice != exit_prog)
    {
        cout << "               Main Menu    " << endl;
        cout << "****************************************" << endl;
        cout << "1. View a team's data" << endl;
        cout << "2. Print a csv of all team's data" << endl;
        cout << "3. Simulate a match" << endl;
        cout << "4. Load New CSV Dataset" << endl;
        cout << "5. Save Data to CSV" << endl;
        cout << "6. Exit program" << endl;
        cin >> choice;

        switch (choice)
        {
        case 1:
            cout << "Please Enter the team's data you want.";
            cin >> team;
            cout << "Team Number,Average Score,Notes Average Score, stdev, driver_score, climbing_score, human_score, match_count" << endl;
            for (size_t y = 0; y < avg_score.size(); ++y)
            {
                if (team_numbers[y] == team)
                {
                    cout << team_numbers[y] << "," << avg_score[y] << "," << notes_avg_score[y] << "," << stdev[y] << "," << driver_score[y] << "," << climbing_score[y] << ',' << human_score[y] << "," << match_count[y] << endl;
                    cout << endl
                         << endl;
                }
            }

            break;
        case 2:
            cout << "Team Number,Average Score,Notes Average Score, stdev, driver_score, climbing_score, human_score, match_count" << endl;
            for (size_t y = 0; y < avg_score.size(); ++y)
            {
                cout << team_numbers[y] << "," << avg_score[y] << "," << notes_avg_score[y] << "," << stdev[y] << "," << driver_score[y] << "," << climbing_score[y] << ',' << human_score[y] << "," << match_count[y] << endl;
                cout << endl
                     << endl;
            }
            break;
        case 3:
            cout << "Welcome to the match simulator." << endl;
            cout << "Blue 1: ";
            cin >> blue1;
            cout << "Blue 2: ";
            cin >> blue2;
            cout << "Blue 3: ";
            cin >> blue3;
            cout << "Red 1: ";
            cin >> red1;
            cout << "Red 2: ";
            cin >> red2;
            cout << "Red 3: ";
            cin >> red3;

            for (size_t y = 0; y < avg_score.size(); ++y)
            {
                if (team_numbers[y] == blue1)
                    blue1_score = avg_score[y];

                else if (team_numbers[y] == blue2)
                    blue2_score = avg_score[y];
                else if (team_numbers[y] == blue3)
                    blue3_score = avg_score[y];
                else if (team_numbers[y] == red1)
                    red1_score = avg_score[y];
                else if (team_numbers[y] == red2)
                    red2_score = avg_score[y];
                else if (team_numbers[y] == red3)
                    red3_score = avg_score[y];
            }

            bluetot = blue1_score + blue2_score + blue3_score;
            redtot = red1_score + red2_score + red3_score;
            cout << "Blue alliance          Red Alliance" << endl;
            cout << blue1 << ": " << fixed << setprecision(2) << blue1_score << "           " << red1 << ": " << fixed << setprecision(2) << red1_score << endl;
            cout << blue2 << ": " << fixed << setprecision(2) << blue2_score << "           " << red2 << ": " << fixed << setprecision(2) << red2_score << endl;
            cout << blue3 << ": " << fixed << setprecision(2) << blue3_score << "           " << red3 << ": " << fixed << setprecision(2) << red3_score << endl;
            cout << endl;
            cout << "Red: " << redtot << endl;
            cout << "Blue: " << bluetot << endl;

            cout << (redtot > bluetot ? "Red Alliance is the projected winner." : "Blue Alliance is the projected winner.") << endl;

            cout << endl
                 << "End of Match Simluation" << endl
                 << endl;

            break;

        case (4):
        {
            char ch_has_header{'n'};
            string filename = "robot_scores.csv"; // Provide the path to your CSV file -- This will serve as a default name as well.

            cout << "Enter filename to load: ";
            cin >> filename;
            cout << '\n';

            cout << "Does this CSV file have a header (y/n): ";
            cin >> ch_has_header;
            cout << '\n';

            auto result = CSVReader(filename).ParseCSV((ch_has_header == 'y' ? true : false)).GetResults();

            vector<vector<int>> matrix{};
            for (const auto &[key, value] : result)
            {
                for (const auto &row : value)
                    matrix.push_back(row);
            }
            break;
        }

        case (5):
        {
            vector<vector<double>> rows{};
            vector<double> row{};
            string filename{"tmp.csv"};

            for (size_t y = 0; y < avg_score.size(); ++y){
                row.clear();
                row.push_back(team_numbers[y]);
                row.push_back(avg_score[y]);
                row.push_back(notes_avg_score[y]);
                row.push_back(stdev[0]);
                row.push_back(driver_score[y]);
                row.push_back(climbing_score[y]);
                row.push_back(human_score[y]);
                row.push_back(match_count[y]);
                rows.push_back(row);
            }

            cout << "Enter filename to save stats to: ";
            cin >> filename;
            cout << '\n';
            CSVWriter(filename).WriteCSV(rows);

            break;
        }

        default:

            if (choice != exit_prog)
            {
                cout << "Please enter a valid choice (1, 2, 3,4,5)";
            }
            break;
        }
        cin.ignore();
    }
    cout << "Ending Program" << endl;

    return 0;
}

// Converts 5232 Google Sheet to a Matrix that supports quick data maniuplation.
void csv_to_matrix(const string &filename, vector<vector<int>> &score_matrix)
{
    ifstream file(filename);

    if (!file.is_open())
    {
        cerr << "Error: Unable to open the file." << filename << '\n';
        exit(1);
    }

    string line{};
    getline(file, line);
    while (getline(file, line))
    {
        vector<int> row{};
        stringstream ss(line);
        string cell{};

        while (getline(ss, cell, ','))
        {
            if (cell.empty())
            {
                row.push_back(0);
            }
            else
            {
                row.push_back(stoi(cell));
            }
        }

        score_matrix.push_back(row);
    }

    file.close();
}
