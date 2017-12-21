-- Time when started
startTime = 0

-- Start timer
function start()
    startTime = GetTime()
end

-- Update timer
function update()
    dmin = GameObject.GetChild(this, "DMin")
    min = GameObject.GetChild(this, "Min")
    dsec = GameObject.GetChild(this, "DSec")
    sec = GameObject.GetChild(this, "Sec")
    time = GetTime() - startTime
    Material.Assign(GameObject.GetComponent(dmin, "Material"), "texture:" .. math.floor(time / 600))
    Material.Assign(GameObject.GetComponent(min, "Material"), "texture:" .. (math.floor(time / 60) % 10))
    Material.Assign(GameObject.GetComponent(dsec, "Material"), "texture:" .. (math.floor(time / 10) % 10))
    Material.Assign(GameObject.GetComponent(sec, "Material"), "texture:" .. (math.floor(time) % 10))
end