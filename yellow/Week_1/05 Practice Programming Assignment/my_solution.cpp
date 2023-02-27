#include <iostream>
#include <vector>
#include <map>
#include <tuple>
#include <algorithm>

using namespace std;

enum class TaskStatus {
	NEW,
	IN_PROGRESS,
	TESTING,
	DONE
};

using TasksInfo = map<TaskStatus, int>;

vector<TaskStatus> meta_ti = {
	TaskStatus::NEW,
	TaskStatus::IN_PROGRESS,
	TaskStatus::TESTING,
	TaskStatus::DONE
};

TaskStatus getNextStatus(TaskStatus now)
{
	uint32_t res_ind;
	for (size_t i = 0; i < meta_ti.size(); i++)
		if(now == meta_ti[i])
			res_ind = (i+1) % 4;

	if (res_ind) 
		return meta_ti[res_ind];
	return meta_ti[3];
}

class TeamTasks {
private:
	map<string, TasksInfo> data;

public:
	// Получить статистику по статусам задач конкретного разработчика
	const TasksInfo& GetPersonTasksInfo(const string& person) const 
	{
		return data.at(person);
	}
  
	// Добавить новую задачу (в статусе NEW) для конкретного разработчитка
	void AddNewTask(const string& person)
	{
		data[person][TaskStatus::NEW]++;
	}
  
	// Обновить статусы по данному количеству задач конкретного разработчика,
	// подробности см. ниже
	tuple<TasksInfo, TasksInfo> PerformPersonTasks(const string& person,
			int task_count) 
	{
		TasksInfo updated, not_updated;
		int32_t count_cp = task_count;
		for (const auto& [key, value] : data[person]) {
			if (key == TaskStatus::DONE or !task_count)
				break;
			int32_t tasks_move = min(task_count, value);
			updated[getNextStatus(key)] = tasks_move;
			task_count -= tasks_move;
		}
		for (const auto& [key, value] : data[person]) {
			if (key == TaskStatus::DONE)
				break;
			int32_t to_sub = count_cp ? min(count_cp, value) : 0;
			count_cp -= to_sub;
			data[person][key] -= to_sub;
			if (data[person][key]) 
				not_updated[key] = data[person][key];
		}

		for (const auto& [key, value] : updated) 
			data[person][key] += value;
		return tie(updated, not_updated);
	}
};

void PrintTasksInfo(TasksInfo tasks_info) {
	cout << tasks_info[TaskStatus::NEW] << " new tasks" <<
		", " << tasks_info[TaskStatus::IN_PROGRESS] << " tasks in progress" <<
		", " << tasks_info[TaskStatus::TESTING] << " tasks are being tested" <<
		", " << tasks_info[TaskStatus::DONE] << " tasks are done" << endl;
}

int main()
{
	TeamTasks tasks;
	for (int i = 0; i < 2; ++i) {
	tasks.AddNewTask("Ivan");
	}
	TasksInfo updated_tasks, untouched_tasks;

	for (int32_t i = 0; i < 7; i++) {
		tie(updated_tasks, untouched_tasks) =
		tasks.PerformPersonTasks("Ivan", 1);
		cout << "Updated Ivan's tasks: ";
		PrintTasksInfo(updated_tasks);
		cout << "Untouched Ivan's tasks: ";
		PrintTasksInfo(untouched_tasks);
	}

	return 0;
}
