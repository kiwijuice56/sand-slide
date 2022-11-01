extends Node
class_name SaveFileManager

@export var sim_holder: Node

func create_save_file(save_name: String) -> SaveFile:
	var date: Dictionary = Time.get_datetime_dict_from_system(true)
	var date_string: String = Time.get_datetime_string_from_datetime_dict(date, false)
	var folder_name: String = save_name + "_" + date_string
	folder_name = folder_name.replace(":", "_")
	var dir: DirAccess = DirAccess.open("res://")
	dir.make_dir(folder_name)
	
	var file = SaveFile.new()
	file.save_name = save_name
	file.date = date_string
	file.version = ProjectSettings.get_setting("application/config/version")
	
	sim_holder.save_image("res://" + folder_name + "/img.png")
	ResourceSaver.save(file, "res://" + folder_name + "/res.tres")
	
	return file
