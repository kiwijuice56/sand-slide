extends Node
class_name SaveFileManager

@export var sim_holder: Node

var files: Array[SaveFile] = []

func _ready() -> void:
	update_files()

func update_files() -> void:
	files.clear()
	var dir: DirAccess = DirAccess.open("user://")
	for folder in dir.get_directories():
		if not folder.begins_with("save"):
			continue
		
		var res: SaveFile = ResourceLoader.load("%s/%s/res.tres" % [dir.get_current_dir(), folder])
		var img_file: FileAccess = FileAccess.open("%s/%s/img.png" % [dir.get_current_dir(), folder], FileAccess.READ)
		res.size = img_file.get_length()
		
		files.append(res)

func create_save_file(save_name: String) -> SaveFile:
	var cleaned_name: String = ""
	for c in save_name:
		if c in "\\/:*?\"<>":
			continue
		if c == " ":
			c = "_"
		cleaned_name += c.to_lower()
	if len(cleaned_name) == 0:
		cleaned_name = "new_file"
	save_name = cleaned_name
	
	var date: Dictionary = Time.get_datetime_dict_from_system(true)
	var date_string: String = Time.get_datetime_string_from_datetime_dict(date, false)
	var folder_name: String = "save_" + save_name + "_" + date_string
	folder_name = folder_name.replace(":", "_")
	var dir: DirAccess = DirAccess.open("user://")
	dir.make_dir(folder_name)
	
	var file = SaveFile.new()
	file.save_name = save_name
	file.date = date_string
	file.version = ProjectSettings.get_setting("application/config/version")
	
	sim_holder.save_image("user://" + folder_name + "/img.png")
	ResourceSaver.save(file, "user://" + folder_name + "/res.tres")
	
	update_files()
	
	return file

func overwrite_save_file(file: SaveFile) -> void:
	var path: String = file.get_path()
	var folder: String = path.substr(0, path.rfind("/") + 1)
	sim_holder.save_image(folder + "/img.png")
	file.version = ProjectSettings.get_setting("application/config/version")
	ResourceSaver.save(file, path)
	
	update_files()

func load_from_file(file: SaveFile) -> void:
	var path: String = file.get_path()
	var folder: String = path.substr(0, path.rfind("/") + 1)
	sim_holder.load_image(folder + "/img.png")

func delete_save_file(file: SaveFile) -> void:
	var path: String = file.get_path()
	var folder: String = path.substr(0, path.rfind("/") + 1)
	var dir: DirAccess = DirAccess.open(folder)
	dir.remove(path)
	dir.remove(folder + "img.png")
	dir.remove("")
	files.remove_at(files.find(file))
	
	update_files()
